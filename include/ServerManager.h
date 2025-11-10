#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <string>
#include <vector>
#include <unordered_set>

class ServerManager {
public:
    explicit ServerManager(const std::string& filename);
    ~ServerManager();

    std::vector<std::string> GetServersList() const;
    bool AddServer(const std::string& ip);
    bool DeleteServer(const std::string& ip);

private:
    void LoadFromFile();
    void ApplyLog();
    void AppendLog(const std::string& entry);
    void SaveToFile() const;
    void ClearLog();

    std::string filename_;
    std::string logname_;
    std::unordered_set<std::string> servers_;
};

#endif
