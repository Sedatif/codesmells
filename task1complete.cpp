void checkSecurity(String[] people) {
    for (String person : people) {
        if (person.equals("Don") || person.equals("John")) {
            sendAlert();
            return;
        }
    }
}