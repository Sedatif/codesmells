# codesmells

### Завдання 1. Рефакторинг на рівні окремих операторів
Наступна функція перевіряє, чи немає підозрілих осіб у списку осіб, імена яких були "захаркоджені":
```
void checkSecurity(String[] people) {
  boolean found = false;
  for (int i = 0; i < people.Length; i++) {
    if (!found) {
      if (people[i].Equals(“Don”)) {
        sendAlert();
        found = true;
      }
      if (people[i].Equals(“John”)) {
        sendAlert();
        found = true;
      }
    }
  }
}
```
Помічені "запахи коду":
```
void checkSecurity(String[] people) {
  boolean found = false;                         ///Забруднювач коду - "мертва" булева змінна, що виступає у ролі керуючого флагу
  for (int i = 0; i < people.Length; i++) {      ///Роздувач коду
    if (!found) {
      if (people[i].Equals(“Don”)) {             ///Забруднювач коду - "дублювання коду"
        sendAlert();
        found = true;
      }
      if (people[i].Equals(“John”)) {            ///Забруднювач коду - "дублювання коду"
        sendAlert();
        found = true;
      }
    }
  }
}
```
Рефакторинг:
1. Видалення керуючого флагу та заміна на return, оскільки при знаходженні хоча б однієї людини з іменем "Don" або "John", ми викликаємо метод sendAlert() та відразу завершуємо цикл, оскільки далі перевіряти вже немає сенсу;
2. Покращення циклу шляхом використання для ітерації елементів масиву людей, тим самим спростити логіку циклу;
3. Прибрати дублювання коду.
```
void checkSecurity(String[] people) {
    for (String person : people) {
        if (person.equals("Don") || person.equals("John")) {
            sendAlert();
            return;
        }
    }
}
```

### Завдання 2. Рефакторинг на рівні даних
```
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
```
Помічені "запахи коду":
```
enum TransportType { /// створити наслідування
  eCar,
  ePlane,
  eSubmarine
};

class Transport {
  public:
    Transport(TransportType type) : m_type (type) {}
    int GetSpeed(int distance, int time) {
      if (time != 0) { /// заміна на if (time == 0){return 0;}
        switch(m_type) { /// конструкція switch буде збільшуватись
          case eCar:
            return distance/time;
          case ePlane:
            return distance/(time - getTakeOffTime() - getLandingTime());  /// використання приватних полів всередині класу.
          case eSubmarine:
            return distance/(time - getDiveTime() - getAscentTime());      /// використання приватних полів всередині класу.
        }
      }
    }
...
  private:
    int m_takeOffTime; /// відсутні методи доступу до приватних змінних
    int m_landingTime;
    int m_diveTime;
    int m_ascentTime;
    enum m_type;
};
```
Рефакторинг:
1. Наслідування елементів enum TransportType від класу Transport;
2. Зміна логіки публічного методу;
3. Заміна конструкції switch;
4. Заміна кодування типу класом;
5. Написання гетерів для доступу до приватних полів;
```
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
```

