//Task 2

// Overloaded < operator.
// TASK 2
//
bool Transaction::operator<( Transaction const &other ) {
  if (this->year < other.get_year()) {
    return true;
  } else if (this->year == other.get_year()) {
      if (this->month < other.get_month()) {
        return true;
        } else if (this->month == other.get_month()) {
          if (this->day < other.get_day()) {
            return true;
          }
      }
    }
  return false;
}
//Task 5

void History::insert(Transaction *p_new_trans){ 
  if (p_head == nullptr) {
    this ->p_head = p_new_trans; 
  }
  else {
    Transaction *p_traverse {p_head};

    while (p_traverse->get_next() != nullptr) {
      p_traverse = p_traverse->get_next();
    }
    p_traverse->set_next(p_new_trans);
  }
}