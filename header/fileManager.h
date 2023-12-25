namespace fileManager {

    std::vector<std::string> read(std::filesystem::path filePath);
    std::vector<std::string> wrap(std::vector<std::string> fileData);
    void print(std::vector<std::string> fileData);

}
