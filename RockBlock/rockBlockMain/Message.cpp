enum MSG_TYPE {
  SND,
  RCV
};

class Message {
  private:
    int timestamp;
    char message[];
    MSG_TYPE type;
};
