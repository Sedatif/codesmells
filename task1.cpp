void checkSecurity(String[] people) {
    boolean found = false;
    for (int i = 0; i < people.Length; i++) {
        if (!found) {
            if (people[i].Equals("Don")) {
                sendAlert();
                found = true;
            }
            if (people[i].Equals("John")) {
                sendAlert();
                found = true;
            }
        }
    }
}