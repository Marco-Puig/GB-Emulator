#include <emu.h>

int main()
{
    std::ifstream file("../../roms/dmg-acid2.gb", std::ios::binary);

    // file failed to open - send error
    if (!file.is_open())
    {
        std::cout << "Error opening file ../../roms/dmg-acid2.gb" << std::endl;
        return 1;
    }

    return emu_run(file);
}
