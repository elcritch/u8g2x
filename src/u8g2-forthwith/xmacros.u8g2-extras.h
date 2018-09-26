
forth_docall(".", 1, F_NORMAL, fw_dot, "( n -- )", doDot);
forth_docall("..", 2, F_NORMAL, fw_dot_dot, "( n -- )", doDotDot);
forth_docall(".x", 2, F_NORMAL, fw_dot_x, "( n -- )", doDotX);
forth_docall("micros", 6, F_NORMAL, fw_micros, "( n -- )", doMicros);
forth_docall("millis", 6, F_NORMAL, fw_millis, "( n -- )", doMillis);
forth_docall("timer0", 6, F_NORMAL, fw_timer0, "( n -- )", doTimer0);


forth_docall("delay-micros", 12, F_NORMAL, fw_delay_micros,
             "( n -- )", doDelayMicro);
forth_docall("delay-millis", 12, F_NORMAL, fw_delay_millis,
             "( n -- )", doDelayMillis);

forth_docall("pin-info", 8, F_NORMAL, fw_pin_info,
             "( n -- port mask )", doPinInfo);
forth_docall("pin-config", 10, F_NORMAL, fw_pin_config,
             "( mode pin -- )", doPinMode);

forth_docall("pin-write", 9, F_NORMAL, fw_pin_write,
             "( val pin -- )", doPinWrite);
forth_docall("pin-read", 8, F_NORMAL, fw_pin_read,
             "( val pin -- )", doPinRead);

forth_docall("pin-write-fast", 14, F_NORMAL, fw_pin_write_fast,
             "( val pin -- )", doPinWriteFast);
forth_docall("pin-write-fast1", 15, F_NORMAL, fw_pin_write_fast1,
             "( val pin -- )", doPinWriteFast1);
forth_docall("pin-read-fast", 13, F_NORMAL, fw_pin_read_fast,
             "( val pin -- )", doPinReadFast);

forth_docall("spi-init", 8, F_NORMAL, fw_init_spi,
             "( -- )", doInitSpi);
forth_docall("spi-config", 10, F_NORMAL, fw_config_spi,
             "( spi-clock spi-order spi-mode spi-num -- valid? )", doConfigSpi);


forth_docall("spi-tx-do", 9, F_NORMAL, fw_spi_tx_do,
             "( cs_pin spi-config -- )", doSpiBegin);
forth_docall("spi-xfer", 8, F_NORMAL, fw_spi_xfer,
             "( data[N] N -- rdata[N] )", doSpiXfer);
forth_docall("spi-read", 8, F_NORMAL, fw_spi_read,
             "( N -- rdata[N] )", doSpiRead);
forth_docall("spi-write", 9, F_NORMAL, fw_spi_write,
             "( data[N] N -- )", doSpiWrite);
forth_docall("spi-tx-end", 10, F_NORMAL, fw_spi_tx_end,
             "( N cs_pin spi-config -- rdata[N] )", doSpiEnd);

