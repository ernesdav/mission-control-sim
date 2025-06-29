#include <gtest/gtest.h>
#include "MissionQueue.h"
#include "DeliveryMission.h"
#include <vector>
#include <thread>
#include <atomic>
#include <mutex> // <-- Incluimos mutex aquí también

// Mutex global (para este archivo de prueba) para proteger std::cout
std::mutex cout_mutex;

// Test Suite para MissionQueue
TEST(MissionQueueTest, HandlesPriorityCorrectly) {
    MissionQueue queue;
    queue.addMission(std::make_shared<DeliveryMission>(1, 3, 0, 0, "Low Prio"));
    queue.addMission(std::make_shared<DeliveryMission>(2, 1, 0, 0, "High Prio"));
    queue.addMission(std::make_shared<DeliveryMission>(3, 2, 0, 0, "Mid Prio"));

    auto mission1 = queue.getNextMission();
    ASSERT_NE(mission1, nullptr);
    EXPECT_EQ(mission1->getId(), 2);

    auto mission2 = queue.getNextMission();
    ASSERT_NE(mission2, nullptr);
    EXPECT_EQ(mission2->getId(), 3);

    auto mission3 = queue.getNextMission();
    ASSERT_NE(mission3, nullptr);
    EXPECT_EQ(mission3->getId(), 1);

    EXPECT_TRUE(queue.isEmpty());
}

TEST(MissionQueueTest, IsThreadSafe) {
    // ARRANGE
    MissionQueue queue;
    std::atomic<int> missions_produced = 0;
    std::atomic<int> missions_consumed = 0;
    const int missions_per_producer = 50;
    const int num_producers = 4;
    const int num_consumers = 4;

    std::vector<std::thread> threads;

    // Creamos hilos productores
    for (int i = 0; i < num_producers; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < missions_per_producer; ++j) {
                int mission_id = i * missions_per_producer + j;
                // La impresión de depuración ahora está protegida
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    // std::cout << "Producing mission " << mission_id << std::endl;
                }
                queue.addMission(std::make_shared<DeliveryMission>(mission_id, 1, 0, 0, "Test Item"));
                missions_produced++;
            }
        });
    }

    // Creamos hilos consumidores
    for (int i = 0; i < num_consumers; ++i) {
        threads.emplace_back([&]() {
            while (missions_consumed < missions_per_producer * num_producers) {
                if (auto mission = queue.getNextMission()) {
                    // La impresión de depuración ahora está protegida
                    {
                        std::lock_guard<std::mutex> lock(cout_mutex);
                        // std::cout << "Consuming mission " << mission->getId() << std::endl;
                    }
                    missions_consumed++;
                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        });
    }

    // ACT
    for (auto& t : threads) {
        t.join();
    }

    // ASSERT
    EXPECT_EQ(missions_produced, missions_per_producer * num_producers);
    EXPECT_EQ(missions_produced, missions_consumed);
    EXPECT_TRUE(queue.isEmpty());
}