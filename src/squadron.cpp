#include "squadron.h"
#include "bomber.h"

Squadron::Squadron(Carrier* carrier, PlaneType type) {
    this->carrier = carrier;
    this->target = nullptr;
    this->type = type;
    // Create 5 planes
    for (int i = 0; i < planeCount; i++) {
        Plane* plane;
        if(type == PlaneType::BOMBER) plane = new Bomber(carrier->GetPosition(), carrier->GetTeam(), carrier);
        else plane = new Plane(carrier->GetPosition(), carrier->GetTeam(), carrier);
        plane->active = false; // Planes are inactive until deployed
        plane->SetSquadron(this);
        squadronPlanes.push_back(plane);
    }
    carrier->AddSquadron(this);
}

Squadron::~Squadron() = default;

void Squadron::Deploy(Ship* target) {
    if(activePlanes != 0 || deploying) return; // Can't give the order to deploy if already deployed
    this->target = target;
    deploying = true;
}

void Squadron::Update() {
    static int delay = 0;
    if (deploying) {
        if (delay > 0) {
            delay--;
            return;
        }
        if (activePlanes < planeCount) {
            Plane* plane = squadronPlanes[activePlanes];
            plane->SetTarget(target);
            plane->active = true;
            activePlanes++;
            delay = 40;
        } else {
            deploying = false;
        }
    }
    // Check for downed planes and delete them
    for (int i = 0; i < squadronPlanes.size(); i++) {
        squadronPlanes[i]->SetTarget(target);
        if (squadronPlanes[i]->downed) {
            Plane* downedPlane = squadronPlanes[i];
            squadronPlanes.erase(squadronPlanes.begin() + i);
            planes.erase(std::remove(planes.begin(), planes.end(), downedPlane), planes.end());
            delete downedPlane;
            i--; // Decrement i because the elements after i have moved down by 1
            activePlanes--; // Decrement the active planes counter
            planeCount--; // Decrement the plane count
        }
    }
}

void Squadron::setTarget(Ship* target) {
    this->target = target;
}

int Squadron::GetActivePlanes() {
    return activePlanes;
}

int Squadron::GetPlaneCount() {
    return planeCount;
}

Carrier* Squadron::GetCarrier() {
    return carrier;
}

void Squadron::SetActivePlanes(int activePlanes) {
    this->activePlanes = activePlanes;
}

void Squadron::SetPlaneCount(int planeCount) {
    this->planeCount = planeCount;
}

void Squadron::SetDeploying(bool deploying) {
    this->deploying = deploying;
}

std::vector<Plane*> Squadron::GetSquadronPlanes() {
    return squadronPlanes;
}

PlaneType Squadron::GetType() {
    return type;
}
