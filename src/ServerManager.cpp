#include "ServerManager.h"
#include <fstream>
#include <iostream>

ServerManager::ServerManager(const std::string& filename)
    : filename_(filename), logname_(filename + ".log") {
    LoadFromFile();
    ApplyLog();
}

ServerManager::~ServerManager() {
    SaveToFile(); 
    ClearLog();   
}

std::vector<std::string> ServerManager::GetServersList() const {
    return {servers_.begin(), servers_.end()};
}

bool ServerManager::AddServer(const std::string& ip) {
    if (servers_.count(ip)) return false;

    AppendLog("ADD " + ip);
    servers_.insert(ip);
    
    std::ofstream file(filename_, std::ios::app);
    if (!file.is_open()) return false;
    file << ip << "\n";
    file.flush();
    return true;
}

bool ServerManager::DeleteServer(const std::string& ip) {
    if (!servers_.erase(ip)) return false;

    AppendLog("DEL " + ip);
    SaveToFile();
    return true;
}

void ServerManager::LoadFromFile() {
    std::ifstream file(filename_);
    std::string ip;
    while (std::getline(file, ip)) {
        if (!ip.empty()) servers_.insert(ip);
    }
}

void ServerManager::ApplyLog() {
    std::ifstream log(logname_);
    std::string op, ip;
    while (log >> op >> ip) {
        if (op == "ADD") servers_.insert(ip);
        else if (op == "DEL") servers_.erase(ip);
    }
}

void ServerManager::AppendLog(const std::string& entry) {
    std::ofstream log(logname_, std::ios::app);
    log << entry << "\n";
    log.flush();
}

void ServerManager::SaveToFile() const {
    std::ofstream file(filename_, std::ios::trunc);
    for (const auto& ip : servers_) {
        file << ip << "\n";
    }
    file.flush();
}

void ServerManager::ClearLog() {
    std::ofstream log(logname_, std::ios::trunc);
}
