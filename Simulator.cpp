#include <utility>

#include <utility>

#include <utility>


//
// Created by Zhou Yitao on 2018-12-04.
//

#include "Simulator.h"
#include <cmath>

using namespace std;

Simulator::Simulator(vector<Flow> flows, vector<Packet> packets) {
//    for (auto flow: flows)
//        this->flows.push_back(flow);
//    for (auto packet: packets)
//        this->packets.push_back(packet);
    this->flows = move(flows);
    this->packets = move(packets);
    currentRound = 0;
    currentCycle = 0;
    currentPacketIndex = 0;
}

vector<Packet> Simulator::runRound() {
    vector<Packet> result;
    Packet tmp = runCycle();
    int currentCycle_backup = currentCycle;
    while (tmp.getPacketOrder() != -1) {
        currentCycle++;
        tmp.setDepartureCycle(currentCycle);
        tmp.setActlDepartureRound(currentRound);
        result.push_back(tmp);
        tmp = runCycle();
    }

    //serve the level1 and level2 fifo
    vector<Packet> upperLevelPackets = scheduler.serveUpperLevel(currentCycle, currentRound);

    result.insert(result.end(), upperLevelPackets.begin(), upperLevelPackets.end());
    //current round done
    currentRound++;
    if (currentCycle == currentCycle_backup)
        currentCycle++;
    scheduler.setCurrentRound(currentRound);
    return result;
}

Packet Simulator::runCycle() {
    //push arrive packets to scheduler
    while (currentPacketIndex < packets.size() && packets[currentPacketIndex].getArriveCycle() <= currentCycle) {
        Packet packet = packets[currentPacketIndex++];
        int departureRound = calDepartureRound(packet.getFlowId() - 1, packet.getSize());
        packet.setThryDepartureRound(departureRound);
        scheduler.push(packet);
    }
    //pull one packet out
    return scheduler.serveCycle();
}

int Simulator::calDepartureRound(int flowId, int packetSize) {
    int departureRound = static_cast<int>(ceil(max(currentRound, flows[flowId].getLastDepartureRound())
            + 1 / flows[flowId].getWeight() * packetSize));
    flows[flowId].setLastDepartureRound(departureRound);
    return departureRound;
}

int Simulator::numOfFlows() {
    return static_cast<int>(flows.size());
}

int Simulator::numOfPackets() {
    return static_cast<int>(packets.size());
}
