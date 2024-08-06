#include <cart.h>

typedef struct
{
    char filename[1024];
    u32 rom_size;
    u8 *rom_data;
    rom_header *header;
} cart_context; // make into class to expand functionality later on

static cart_context ctx;

static const char *ROM_TYPES[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

static const char *LIC_CODE[0xA5];

void initializeLIC_CODE()
{
    LIC_CODE[0x00] = "None";
    LIC_CODE[0x01] = "Nintendo R&D1";
    LIC_CODE[0x08] = "Capcom";
    LIC_CODE[0x13] = "Electronic Arts";
    LIC_CODE[0x18] = "Hudson Soft";
    LIC_CODE[0x19] = "b-ai";
    LIC_CODE[0x20] = "kss";
    LIC_CODE[0x22] = "pow";
    LIC_CODE[0x24] = "PCM Complete";
    LIC_CODE[0x25] = "san-x";
    LIC_CODE[0x28] = "Kemco Japan";
    LIC_CODE[0x29] = "seta";
    LIC_CODE[0x30] = "Viacom";
    LIC_CODE[0x31] = "Nintendo";
    LIC_CODE[0x32] = "Bandai";
    LIC_CODE[0x33] = "Ocean/Acclaim";
    LIC_CODE[0x34] = "Konami";
    LIC_CODE[0x35] = "Hector";
    LIC_CODE[0x37] = "Taito";
    LIC_CODE[0x38] = "Hudson";
    LIC_CODE[0x39] = "Banpresto";
    LIC_CODE[0x41] = "Ubi Soft";
    LIC_CODE[0x42] = "Atlus";
    LIC_CODE[0x44] = "Malibu";
    LIC_CODE[0x46] = "angel";
    LIC_CODE[0x47] = "Bullet-Proof";
    LIC_CODE[0x49] = "irem";
    LIC_CODE[0x50] = "Absolute";
    LIC_CODE[0x51] = "Acclaim";
    LIC_CODE[0x52] = "Activision";
    LIC_CODE[0x53] = "American sammy";
    LIC_CODE[0x54] = "Konami";
    LIC_CODE[0x55] = "Hi tech entertainment";
    LIC_CODE[0x56] = "LJN";
    LIC_CODE[0x57] = "Matchbox";
    LIC_CODE[0x58] = "Mattel";
    LIC_CODE[0x59] = "Milton Bradley";
    LIC_CODE[0x60] = "Titus";
    LIC_CODE[0x61] = "Virgin";
    LIC_CODE[0x64] = "LucasArts";
    LIC_CODE[0x67] = "Ocean";
    LIC_CODE[0x69] = "Electronic Arts";
    LIC_CODE[0x70] = "Infogrames";
    LIC_CODE[0x71] = "Interplay";
    LIC_CODE[0x72] = "Broderbund";
    LIC_CODE[0x73] = "sculptured";
    LIC_CODE[0x75] = "sci";
    LIC_CODE[0x78] = "THQ";
    LIC_CODE[0x79] = "Accolade";
    LIC_CODE[0x80] = "misawa";
    LIC_CODE[0x83] = "lozc";
    LIC_CODE[0x86] = "Tokuma Shoten Intermedia";
    LIC_CODE[0x87] = "Tsukuda Original";
    LIC_CODE[0x91] = "Chunsoft";
    LIC_CODE[0x92] = "Video system";
    LIC_CODE[0x93] = "Ocean/Acclaim";
    LIC_CODE[0x95] = "Varie";
    LIC_CODE[0x96] = "Yonezawa/s’pal";
    LIC_CODE[0x97] = "Kaneko";
    LIC_CODE[0x99] = "Pack in soft";
    LIC_CODE[0xA4] = "Konami (Yu-Gi-Oh!)";
}

const char *cart_lic_name()
{
    initializeLIC_CODE();
    if (ctx.header->new_lic_code <= 0xA4)
    {
        return LIC_CODE[ctx.header->lic_code];
    }

    return "UNKNOWN";
}

const char *cart_type_name()
{
    if (ctx.header->type <= 0x22)
    {
        return ROM_TYPES[ctx.header->type];
    }

    return "UNKNOWN";
}

bool cart_load(std::ifstream &file)
{
    // updated file reading
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());

    if (buffer.empty())
    {
        std::cerr << "Failed to read cartridge file" << std::endl;
        return false;
    }

    ctx.rom_size = buffer.size();
    ctx.rom_data = static_cast<u8 *>(malloc(ctx.rom_size));

    if (!ctx.rom_data)
    {
        std::cerr << "Failed to allocate memory for ROM data" << std::endl;
        return false;
    }

    std::copy(buffer.begin(), buffer.end(), static_cast<unsigned char *>(ctx.rom_data));

    ctx.header = (rom_header *)(ctx.rom_data + 0x100);
    ctx.header->title[15] = 0;

    std::cout << "Cartridge Loaded:\n";
    std::cout << "\t Title    : " << ctx.header->title << "\n";
    std::cout << "\t Type     : " << std::hex << (int)ctx.header->type << " (" << cart_type_name() << ")\n";
    std::cout << "\t ROM Size : " << (32 << ctx.header->rom_size) << " KB\n";
    std::cout << "\t RAM Size : " << std::hex << (int)ctx.header->ram_size << "\n";
    std::cout << "\t LIC Code : " << std::hex << (int)ctx.header->lic_code << " (" << cart_lic_name() << ")\n";
    std::cout << "\t ROM Vers : " << std::hex << (int)ctx.header->version << "\n";

    u16 x = 0;
    for (u16 i = 0x0134; i <= 0x014C; i++)
    {
        x = x - ctx.rom_data[i] - 1;
    }

    std::cout << "\t Checksum : " << std::hex << (int)ctx.header->checksum << " (" << ((x & 0xFF) ? "PASSED" : "FAILED") << ")\n";

    return true;
}
