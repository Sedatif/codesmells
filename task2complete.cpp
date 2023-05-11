class Transport {
public:
    virtual ~Transport() = default;
    virtual int GetSpeed(int distance, int time) const = 0;
};

class Car : public Transport {
public:
    int GetSpeed(int distance, int time) const override {
        if (time == 0) {
            return 0;
        }
        return distance / time;
    }
};

class Plane : public Transport {
public:
    Plane(int takeOffTime, int landingTime) 
        : m_takeOffTime(takeOffTime), m_landingTime(landingTime) {}

    int GetSpeed(int distance, int time) const override {
        if (time == 0) {
            return 0;
        }
        time -= GetTakeOffTime() + GetLandingTime();
        return distance / time;
    }

    int GetTakeOffTime() const { return m_takeOffTime; }
    int GetLandingTime() const { return m_landingTime; }

private:
    int m_takeOffTime;
    int m_landingTime;
};

class Submarine : public Transport {
public:
    Submarine(int diveTime, int ascentTime) 
        : m_diveTime(diveTime), m_ascentTime(ascentTime) {}

    int GetSpeed(int distance, int time) const override {
        if (time == 0) {
            return 0;
        }
        time -= GetDiveTime() + GetAscentTime();
        return distance / time;
    }

    int GetDiveTime() const { return m_diveTime; }
    int GetAscentTime() const { return m_ascentTime; }

private:
    int m_diveTime;
    int m_ascentTime;
};