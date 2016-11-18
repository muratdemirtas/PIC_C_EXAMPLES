#ifndef dht11
   #define dht11 PIN_C3
#endif

char dht_dat[10]; // Output data will be here

void dht_init()

{
    delay_ms (1);
    OUTPUT_HIGH (dht11);
}
byte leer_dht_dat()

{
    byte i = 0;
    byte result = 0;

    for (i = 0; i < 8; i++)
    {
        while (input (dht11) == 0)
            ;

        delay_us (30);

        if (input (dht11) == 1)
        {
            result |= (1 << (7 - i) );
        }

        while (input (dht11) == 1)
            ;
    }

    return result;
}

void read_dht()

{
    byte GlobalErr = 0;
    byte dht_in;
    byte i;
    byte dht_check_sum;
    dht_init();
    OUTPUT_LOW (dht11);
    delay_ms (18);
    OUTPUT_HIGH (dht11);
    delay_us (30);
    dht_in = input (dht11);

    if (dht_in)
    {
        GlobalErr = 1;
        return;
    }

    delay_us (80);
    dht_in = input (dht11);

    if (!dht_in)
    {
        GlobalErr = 2;
        return;
    }

    delay_us (80);

    for (i = 0; i < 4; i++)
    {
        dht_dat[i] = leer_dht_dat();
    }

    OUTPUT_HIGH (dht11);
}


