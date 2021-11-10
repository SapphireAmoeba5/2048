#include <2048util.h>




std::string LoadVariable(const std::string& buffer, const std::string& name, size_t offset, size_t* end, bool* ret)
{
    int index;
    if((index = buffer.find(name+"=", offset)) == std::string::npos)
    {
        CONSOLE_PRINT("WARNING : Failed to find '"<<name<<"' in INI file");
        *ret = false;
        return "";
    }

    *end = buffer.find('\n', index) + 1;
    *ret = true;
    return buffer.substr(index + name.size() + 1, (*end) - (index + name.size()) - 1);

}

void ResetIniFile(const char* path)
{
    const char* const default_ini_file = "boardSizeX=4\n"
                                        "boardSizeY=4";

    std::ofstream outFile(path);
    outFile.write(default_ini_file, strlen(default_ini_file));
    outFile.close();
}

bool LoadIniFile(const char* path, glm::vec2* boardSize)
{
    std::string file;
    
    std::ifstream inFile(path);

    // If the file doesn't exist or is otherwise unopenable
    if(inFile.bad() || !inFile.is_open())
    {
        inFile.close();
        ResetIniFile(path);

        (*boardSize).x = 4;
        (*boardSize).y = 4;

        CONSOLE_PRINT("WARNING : INI file not found. Recreating it");
        return false;
    }

    // Getting the size of the file
    inFile.seekg(0, std::ios_base::end);
    size_t fileSize = inFile.tellg();
    inFile.seekg(0, std::ios_base::beg);

    char* buffer = new char[fileSize + 1];
    buffer[fileSize] = 0; // Null terminated byte

    inFile.read(buffer, fileSize);
    inFile.close();
    
    file = buffer;
    delete[] buffer;


    // Loading 'boardSizeX'
    size_t end = 0;
    bool ret;
    std::string boardSizeX = LoadVariable(file, "boardSizeX", end, &end, &ret);
    if(!ret) // Check for errors
    {
        (*boardSize).x = 4;
        (*boardSize).y = 4;
        return false;
    }

    // Loading 'boardSizeY'
    std::string boardSizeY = LoadVariable(file, "boardSizeY", end, &end, &ret);
    if(!ret) // Check for errors
    {
        (*boardSize).x = 4;
        (*boardSize).y = 4;
        return false;
    }
    
    // Try in case std::stof fails
    try
    {
        (*boardSize).x = std::stof(boardSizeX);
        (*boardSize).y = std::stof(boardSizeY);
    }
    catch(const std::exception& e)
    {
        std::cerr<<"WARNING : Error loading variable in INI file. Recreating it with default values\n";
        ResetIniFile(path);
        (*boardSize).x = 4;
        (*boardSize).y = 4;
        return false;
    }
    

    return true;
}