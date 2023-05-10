enum class TransportType {
    eCar,
    ePlane,
    eSubmarine
};

class Transport {
    public:
        Transport(TransportType type) : m_type(type) {}
        
        int GetSpeed(int distance, int time) const {
            if (time == 0) {
                return 0;
            }
            if (m_type == TransportType::ePlane) {
                time -= getTakeOffTime() + getLandingTime();
            } else if (m_type == TransportType::eSubmarine) {
                time -= getDiveTime() + getAscentTime();
            }
            return distance / time;
        }

    private:
        TransportType m_type;
        int m_takeOffTime = 0;
        int m_landingTime = 0;
        int m_diveTime = 0;
        int m_ascentTime = 0;
        
        int getTakeOffTime() const { return m_takeOffTime; }
        int getLandingTime() const { return m_landingTime; }
        int getDiveTime() const { return m_diveTime; }
        int getAscentTime() const { return m_ascentTime; }
};