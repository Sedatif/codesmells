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
enum TransportType {
  eCar,
  ePlane,
  eSubmarine
};

class Transport {
  public:
    Transport(TransportType type) : m_type (type) {}
    int GetSpeed(int distance, int time) {
      if (time != 0) { /// заміна на if (time == 0){return 0;}
        switch(m_type) { /// конструкція switch
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
    int m_takeOffTime; ///ініціалізація приватних змінних не є коректною
    int m_landingTime;
    int m_diveTime;
    int m_ascentTime;
    enum m_type; /// не є приватним
};
```
Рефакторинг:
1. Зміна логіки публічного методу;
2. Заміна конструкції switch;
3. Написання гетерів для доступу до приватних полів;
4. Приватні змінні ініціалізовано коректно (int m_takeOffTime = 0;);
5. Зробити enum m_type приватним шляхом типізації (TransportType m_type;);
```
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
```

