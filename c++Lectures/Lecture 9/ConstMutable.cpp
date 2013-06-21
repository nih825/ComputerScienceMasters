struct constStruct {
  void setI(int newVal) {
    i = newVal;
    count++;
  }
  int getI() const {
    (const_cast<unsigned &>(count))++;
    return i;
  }
  int i;
  unsigned count;
};

struct mutableStruct {
  void setI(int newVal) {
    i = newVal;
    count++;
  }
  int getI() const {
    count++;
    return i;
  }
  int i;
  mutable unsigned count;
};