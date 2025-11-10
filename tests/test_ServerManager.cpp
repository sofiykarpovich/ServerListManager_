#include <gtest/gtest.h>
#include "ServerManager.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class ServerManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        testFile = "test_servers.txt";
        logFile = testFile + ".log";
        Cleanup();
        manager = std::make_unique<ServerManager>(testFile);
    }

    void TearDown() override {
        Cleanup();
    }

    void Cleanup() {
        if (fs::exists(testFile)) fs::remove(testFile);
        if (fs::exists(logFile)) fs::remove(logFile);
    }

    std::unique_ptr<ServerManager> manager;
    std::string testFile;
    std::string logFile;
};

TEST_F(ServerManagerTest, AddAndGetServer) {
    EXPECT_TRUE(manager->AddServer("192.168.1.1"));
    EXPECT_TRUE(manager->AddServer("10.0.0.5"));

    auto list = manager->GetServersList();
    EXPECT_EQ(list.size(), 2);
}

TEST_F(ServerManagerTest, PreventDuplicateServer) {
    EXPECT_TRUE(manager->AddServer("192.168.1.1"));
    EXPECT_FALSE(manager->AddServer("192.168.1.1"));
}

TEST_F(ServerManagerTest, DeleteServer) {
    manager->AddServer("192.168.1.1");
    EXPECT_TRUE(manager->DeleteServer("192.168.1.1"));
    EXPECT_FALSE(manager->DeleteServer("192.168.1.1"));
}

TEST_F(ServerManagerTest, DeleteNonExistingServer) {
    EXPECT_FALSE(manager->DeleteServer("8.8.8.8"));
}

TEST_F(ServerManagerTest, LogRecoveryAfterCrash) {
    {
        std::ofstream log("test_servers.txt.log", std::ios::app);
        log << "ADD 203.0.113.5\n";
    }

    manager = std::make_unique<ServerManager>(testFile);
    auto list = manager->GetServersList();
    EXPECT_TRUE(std::find(list.begin(), list.end(), "203.0.113.5") != list.end());
}
