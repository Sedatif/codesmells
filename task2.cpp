enum TransportType {
    eCar,
    ePlane,
    eSubmarine
};

class Transport {
    public:
        Transport(TransportType type) : m_type (type) {}
        int GetSpeed(int distance, int time) {
        if (time != 0) {
            switch(m_type) {
                case eCar:
                    return distance/time;
                case ePlane:
                    return distance/(time - getTakeOffTime() - getLandingTime());
                case eSubmarine:
                    return distance/(time - getDiveTime() - getAscentTime());
                }
            }
        }
    ...
    private:
        int m_takeOffTime;
        int m_landingTime;
        int m_diveTime;
        int m_ascentTime;
        enum m_type;
};