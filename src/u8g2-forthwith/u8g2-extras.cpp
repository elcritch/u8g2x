

#include "Arduino.h"
// #include "Time.h"
#include "SPI.h"

#undef max
#undef min

/* extern long micros(); */
/* extern long millis(); */

// #ifdef __cplusplus
// #endif

#include <vector>

#include "cortex-extras.h"
#include "forthwith-cortex.h"

extern "C" {


  // Define Primitives, including function bodies, etc
#define FORTH_DEFINE_PRIMITIVES
#include "../forthwith/src/xmacros.h"
#include "../impl/xmacros.cortex-extras.h"
#undef FORTH_DEFINE_PRIMITIVES

  void doDot() {
    fcell_t n = forth_pop();

    String s = String(n);

    write_str(s.length(), (char *)s.c_str());
  }

  void doDotDot() {
    fcell_t n = *(ctx_psp->head-1);

    String s = String(n);

    write_str(s.length(), (char *)s.c_str());
  }

  void doDotX() {
    fcell_t n = forth_pop();

    String s = String(n, HEX);

    write_str(s.length(), (char *)s.c_str());
  }

  void doPinInfo() {
    uint8_t ulPin = (uint8_t)forth_pop();

    // EPortType port = g_APinDescription[pin_number].ulPort;

    EPortType port = g_APinDescription[ulPin].ulPort;
    uint32_t pin = g_APinDescription[ulPin].ulPin;

    // PortGroup* pin_port = &PORT->Group[port];

    forth_push((fcell_t)port);
    forth_push((fcell_t)pin);
  }

  void doPinWriteFast() {
    uint32_t pin =(uint32_t)forth_pop();
    EPortType port =(EPortType)forth_pop();

    uint8_t pin_val =(uint8_t)forth_pop();

    // Serial.write(" val: "); Serial.print(pin_val);
    // Serial.write(" pin: "); Serial.print(pin);
    // Serial.write(" port: "); Serial.print(port);
    // Serial.write(" outclr: "); Serial.print((long int)&PORT->Group[port].OUTCLR.reg );
    // Serial.write(" outset: "); Serial.print((long int)&PORT->Group[port].OUTSET.reg );

    uint32_t pinMask = (1ul << pin);

    // Serial.write(" mask: "); Serial.print(pinMask);

    switch ( pin_val  )
      {
      case 0: // LOW
        PORT->Group[port].OUTCLR.reg = pinMask;
        break ;

      case 1: // HIGH
      default:
        PORT->Group[port].OUTSET.reg = pinMask;
        break ;
      }

  }

  void doPinWriteFast1()
  {
    uint32_t ulVal =(uint32_t)forth_pop();
    uint8_t ulPin =(uint8_t)forth_pop();

    // Handle the case the pin isn't usable as PIO
    if ( g_APinDescription[ulPin].ulPinType == PIO_NOT_A_PIN )
      {
        return ;
      }

    EPortType port = g_APinDescription[ulPin].ulPort;
    uint32_t pin = g_APinDescription[ulPin].ulPin;
    uint32_t pinMask = (1ul << pin);

    if ( (PORT->Group[port].DIRSET.reg & pinMask) == 0 ) {
      // the pin is not an output, disable pull-up if val is LOW, otherwise enable pull-up
      PORT->Group[port].PINCFG[pin].bit.PULLEN = ((ulVal == LOW) ? 0 : 1) ;
    }

    Serial.write(" val: "); Serial.print(ulVal);
    Serial.write(" LOW: "); Serial.print(LOW);
    Serial.write(" pin: "); Serial.print(pin);
    Serial.write(" port: "); Serial.print(port);
    Serial.write(" mask: "); Serial.print(pinMask);
    Serial.write(" outclr: "); Serial.print((long int)&PORT->Group[port].OUTCLR.reg );
    Serial.write(" outset: "); Serial.print((long int)&PORT->Group[port].OUTSET.reg );

    switch ( ulVal )
      {
      case LOW:
        PORT->Group[port].OUTCLR.reg = pinMask;
        break ;

      default:
        PORT->Group[port].OUTSET.reg = pinMask;
        break ;
      }

    return ;
  }

  void doPinReadFast() {
    uint32_t mask =(uint32_t)forth_pop();
    uint32_t port =(uint32_t)forth_pop();

  }

  void doDelayMicro() {
    fcell_t ts = forth_pop();

    long t0 = micros();

    while (micros() - t0 <= ts) {
      __asm__("nop");
    }
  }

  void doDelayMillis() {
    fcell_t ts = forth_pop();

    long t0 = millis();
    while (millis() - t0 <= ts) {
      __asm__("nop");
    }
  }

  void doPinMode() {
    uint8_t pin = forth_pop();
    uint8_t mode = forth_pop();

    switch (mode) {
    case 1:
      pinMode(pin, OUTPUT);
      break;
    case -1:
      pinMode(pin, INPUT);
      break;
    default:
        return;
    }
  }

  void doPinWrite() {
    uint32_t pin = (uint32_t)forth_pop();
    bool value = (bool)forth_pop();

    digitalWrite(pin, value);
  }

  void doPinRead() {
    uint32_t pin = (uint32_t)forth_pop();
    bool value = digitalRead(pin);
    forth_push(value);
  }

  const uint8_t SPI_MAX = 3;
  const uint8_t MAX_SPI_BYTES = 8;
  SPISettings spi_setting[SPI_MAX]; //(2000000, MSBFIRST, SPI_MODE1);

  void doInitSpi() {
    SPI.begin();
  }

  void doConfigSpi() {

    uint8_t spi_num = (uint8_t)forth_pop();
    uint8_t mode = (uint8_t)forth_pop();
    enum BitOrder order = (enum BitOrder)forth_pop();
    uint32_t clock = (uint32_t)forth_pop();

    if (spi_num < SPI_MAX) {
      spi_setting[spi_num] = SPISettings(clock, order, mode);
      forth_push(1);
    } else {
      forth_push(0);
    }
  }

  uint32_t cs_pin = 0;

  void doSpiBegin() {
    uint8_t spi_num = (uint8_t)forth_pop();
    cs_pin = (uint8_t)forth_pop();

    SPISettings spi_conf = spi_setting[spi_num];

    SPI.beginTransaction(spi_conf);
    digitalWrite(cs_pin, LOW);
  }

  void doSpiEnd() {
    digitalWrite(cs_pin, HIGH);
    SPI.endTransaction();
  }

  // transfers bytes in data array and returns readings into the data
  void spi_xfer(uint8_t cnt, uint8_t data[]) {
    for (uint i = 0; i < cnt; i++) {
      uint8_t r = SPI.transfer(data[i]);
      data[i] = r; // update in place
    }
  }

  void doSpiXfer() {
    uint8_t cnt = (uint8_t)forth_pop();

    uint8_t data[8] { 0 };

    for (int i = cnt - 1; i >= 0 ; i--) {
      data[i] = (uint8_t)forth_pop();
    }

    spi_xfer(cnt, data);

    for (int i = 0; i < cnt ; i++) {
      forth_push(data[i]);
    }
  }

  void doSpiRead() {
    uint8_t cnt = (uint8_t)forth_pop();

    uint8_t data[8] { 0 };

    spi_xfer(cnt, data);

    for (int i = 0; i < cnt ; i++) {
      forth_push(data[i]);
    }
  }

  void doSpiWrite() {
    uint8_t cnt = (uint8_t)forth_pop();

    uint8_t data[8] { 0 };

    for (int i = cnt - 1; i >= 0 ; i--) {
      data[i] = (uint8_t)forth_pop();
    }

    spi_xfer(cnt, data);
  }

/* #include <Time.h> */

void doTimer0() {
}

void doMicros() {
  fcell_t ts = (fcell_t)micros();
  forth_push(ts);
}

void doMillis() {
  fcell_t ts = (fcell_t)millis();
  forth_push(ts);
}

int forth_cortex_bootstrap() {

  #define FORTH_DEFINE_DICT_ENTRIES
    #include "../forthwith/src/xmacros.h"
    #ifndef FW_NO_EXTRAS
      #include "../impl/xmacros.cortex-extras.h"
    #endif // FW_NO_EXTRAS
  #undef FORTH_DEFINE_DICT_ENTRIES

  return FW_OK;
}


}
// #ifdef __cplusplus
// }
// #endif

