//
// Created by Zhou Yitao on 2018-12-04.
//

#include "Packet.h"

Packet::Packet(int flowNum, int packageNum, int arriveCycle,
        int departureRound, int departureCycle, int size){
    this->flowId = flowNum;
    this->packetOrder = packageNum;
    this->arriveCycle = arriveCycle;
    this->departureCycle = departureCycle;
    this->thryDepartureRound = departureRound;
    this->actlDepartureRound = -1;
    this->size = size;
}

int Packet::getThryDepartureRound() const {
    return thryDepartureRound;
}

int Packet::getFlowId() const {
    return flowId;
}

int Packet::getArriveCycle() const {
    return arriveCycle;
}

void Packet::setThryDepartureRound(int departureRound) {
    this->thryDepartureRound = departureRound;
};

int Packet::getSize() const {
    return size;
}

int Packet::getPacketOrder() const {
    return packetOrder;
}

int Packet::getDepartureCycle() const {
    return departureCycle;
}

void Packet::setDepartureCycle(int departureCycle) {
    Packet::departureCycle = departureCycle;
}

int Packet::getActlDepartureRound() const {
    return actlDepartureRound;
}

void Packet::setActlDepartureRound(int actlDepartureRound) {
    Packet::actlDepartureRound = actlDepartureRound;
}
