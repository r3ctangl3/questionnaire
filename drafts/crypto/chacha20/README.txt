Related RFC:

    RFC8439
    https://datatracker.ietf.org/doc/html/rfc8439


Endianness comment:

    According to RFC some values must be considered as little-endian
    even on big-endian setups, for example let take a following word:

        uint8_t array[4] = { 0x00, 0x01, 0x02, 0x03 };
        uint32_t word = *(uint32_t*)array;

    value of 'word' will differ from setup to setup:
    -> on little-endian setup   word = 0x03020100
    -> on big-endian setup      word = 0x00010203

    So if RFC requires to consider incoming bytes chunk as
    little-endian and we are on little-endian setup, we do just:

        uint32_t dest;
        memcpy(&dest, &word, 4);

    In opposit, if RFC requires consider incoming bytes array as
    little-endian but we are on big-endian setup, we have swap bytes:

        uint32_t dest;
        memcpy(&dest, &word, 4);
        dest = swap_bytes(dest);
