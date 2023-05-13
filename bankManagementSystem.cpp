#include "bankManagementSystem.h"

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

namespace ICS45C {
namespace BankManagementSystem {

Record *openAccount(Record *accounts, std::string fname, std::string lname,
                    std::string email, std::string phone) {
  static unsigned static_id = 0;
  Record *node = new Record();
  node->fname = fname;
  node->lname = lname;
  node->phone = phone;
  node->email = email;
  node->locked = false;
  node->balance = 0.0;
  node->id = static_id;
  static_id++;
  if (accounts == nullptr) {
    accounts = node;
  } else {
    Record *last = accounts;
    while (last->next != nullptr) last = last->next;
    last->next = node;
  }
  return accounts;
}
void lockAccount(Record *account) {
  if (account != nullptr) {
    account->locked = true;
  }
}
void unlockAccount(Record *account) {
  if (account != nullptr) {
    account->locked = false;
  }
}
Record *searchAccount(Record *accounts, std::string field,
                      std::string keyword) {
  while (accounts != NULL) {
    if (field == "ID" || field == "FIRST" || field == "LAST" ||
        field == "EMAIL" || field == "PHONE") {
      if (accounts->locked == false) {
        if (field == "ID") {
          if (accounts->id == stoul(keyword)) {
            return accounts;
          }
        } else if (field == "FIRST") {
          if (accounts->fname == keyword) {
            return accounts;
          }
        } else if (field == "LAST") {
          if (accounts->lname == keyword) {
            return accounts;
          }
        } else if (field == "EMAIL") {
          if (accounts->email == keyword) {
            return accounts;
          }
        } else if (field == "PHONE") {
          if (accounts->phone == keyword) {
            return accounts;
          }
        }
      }
    }
    accounts = accounts->next;
  }
  return nullptr;
}
string printDetails(Record *account) {
  stringstream output;
  output << "------" << endl;
  if (account == nullptr) {
    output << "Account UNKNOWN" << endl;
    output << "------" << endl;
    output << "Sorry, this account does not exist." << endl;
    output << "------" << endl;
  } else if (account->locked == true) {
    output << "Account #" << account->id << endl;
    output << "------" << endl;
    output << "Sorry, this account has been locked." << endl;
    output << "------" << endl;
  } else if (account->locked == false && account != nullptr) {
    output << "Account #" << account->id << endl;
    output << "------" << endl;
    output << "Status: OPEN" << endl;
    output << "Account holder: " << account->fname << " " << account->lname
           << endl;
    output << "Contact: " << account->phone << " / " << account->email << endl;
    output << "Balance: " << fixed << setprecision(2) << account->balance
           << endl;
    output << "------" << endl;
  }
  return output.str();
}
std::string printDetails(Record *accounts, unsigned int id) {
  bool match = false;
  stringstream output;
  while (accounts != NULL and match != true) {
    if (accounts->locked == false && accounts->id == id) {
      output << "------" << endl;
      output << "Account #" << accounts->id << endl;
      output << "------" << endl;
      output << "Status: OPEN" << endl;
      output << "Account holder: " << accounts->fname << " " << accounts->lname
             << endl;
      output << "Contact: " << accounts->phone << " / " << accounts->email
             << endl;
      output << "Balance: " << fixed << setprecision(2) << accounts->balance
             << endl;
      output << "------" << endl;
      match = true;
    } else if (accounts->locked == true && accounts->id == id) {
      output << "------" << endl;
      output << "Account #" << accounts->id << endl;
      output << "------" << endl;
      output << "Sorry, this account has been locked." << endl;
      output << "------" << endl;
      match = true;
    } else {
      accounts = accounts->next;
    }
  }
  if (accounts == nullptr || match == false) {
    output << "------" << endl;
    output << "Account UNKNOWN" << endl;
    output << "------" << endl;
    output << "Sorry, this account does not exist." << endl;
    output << "------" << endl;
  }
  return output.str();
}
void updateAccount(Record *account, std::string firstName, std::string lastName,
                   std::string phone, std::string email, bool locked) {
  if (account != NULL) {
    account->fname = firstName;
    account->lname = lastName;
    account->phone = phone;
    account->email = email;
    account->locked = locked;
  }
}
void updateAccount(Record *accounts, unsigned int id, std::string firstName,
                   std::string lastName, std::string phone, std::string email,
                   bool locked) {
  bool match = false;
  while (accounts != NULL && match != true) {
    if (accounts->id == id) {
      accounts->fname = firstName;
      accounts->lname = lastName;
      accounts->phone = phone;
      accounts->email = email;
      accounts->locked = locked;
      match = true;
    } else {
      accounts = accounts->next;
    }
  }
}
double deposit(Record *account, double value) {
  if (account == NULL) {
    return -123.45;
  } else if (account->locked == true) {
    return -123.45;
  } else if (value >= 0) {
    account->balance = account->balance + value;
    return account->balance;
  } else {
    return account->balance;
  }
}
double deposit(Record *accounts, unsigned int id, double value) {
  bool match = false;
  double invalid = -123.45;
  while (accounts != NULL && match != true) {
    if (accounts->id == id && accounts->locked == false) {
      if (value >= 0) {
        accounts->balance = accounts->balance + value;
        match = true;
      }
      return accounts->balance;
    } else {
      accounts = accounts->next;
    }
  }
  return invalid;
}
double withdrawal(Record *account, double value) {
  if (account == NULL) {
    return -123.45;
  } else if (account->locked == true) {
    return -123.45;
  } else if (value >= 0) {
    account->balance = account->balance - value;
    return account->balance;
  } else {
    return account->balance;
  }
}
double withdrawal(Record *accounts, unsigned int id, double value) {
  bool match = false;
  double invalid = -123.45;
  while (accounts != NULL && match != true) {
    if (accounts->id == id && accounts->locked == false) {
      if (value >= 0) {
        accounts->balance = accounts->balance - value;
        match = true;
      }
      return accounts->balance;
    } else {
      accounts = accounts->next;
    }
  }
  return invalid;
}
Record *deleteAccount(Record *accounts, unsigned int id) {
  Record *temp = accounts;
  Record *base = accounts;
  while (base != NULL) {
    if (base->id != id) {
      base = base->next;
    } else if ((base->id != id) && (base->next == nullptr)) {
      return accounts;
    } else if (base->id == id) {
      break;
    }
  }
  while (temp != NULL) {  // account not empty, id not match
    if (temp->id == id) {
      Record *t = accounts;
      if (temp == accounts) {  // if wanna delete head
        accounts = accounts->next;
        delete t;
        return accounts;  // delete middle or tail
      }
    } else {
      if (temp->next->next == nullptr) {  // 2-> 3-> null
        if (temp->next->id == id) {       // 2->3
          temp->next = nullptr;
          return accounts;
        }
        if (temp->id != id) {
          return accounts;
        }
      } else {
        if (temp->next->id == id) {
          temp->next = temp->next->next;
          return accounts;
        }
        temp = temp->next;
        if (temp == nullptr) {
          return accounts;
        }
      }
    }
  }
  return accounts;
}
unsigned int countUnlockedAccounts(Record *accounts) {
  unsigned int count_unlocked = 0;
  if (accounts == NULL) {
    return count_unlocked;
  } else {
    while (accounts != NULL) {
      if (accounts->locked == false) {
        count_unlocked++;
        accounts = accounts->next;
      } else {
        accounts = accounts->next;
      }
    }
  }
  return count_unlocked;
}
unsigned int countLockedAccounts(Record *accounts) {
  unsigned int count_locked = 0;
  if (accounts == NULL) {
    return count_locked;
  } else {
    while (accounts != NULL) {
      if (accounts->locked == true) {
        count_locked++;
        accounts = accounts->next;
      } else {
        accounts = accounts->next;
      }
    }
  }
  return count_locked;
}
unsigned int countAllAccounts(Record *accounts) {
  unsigned int count_all = 0;
  if (accounts == NULL) {
    return count_all;
  } else {
    while (accounts != NULL) {
      if (accounts->locked == true || accounts->locked == false) {
        count_all++;
        accounts = accounts->next;
      } else {
        accounts = accounts->next;
      }
    }
  }
  return count_all;
}
long double getAverageBalance(Record *accounts) {
  long double total_balance = 0.0;
  long double total_accounts = 0.0;
  long double average_balance = 0.0;
  long double zero = 0;
  if (accounts == NULL) {
    return zero;
  } else {
    while (accounts != NULL) {
      if (accounts->locked == false) {
        total_balance = total_balance + accounts->balance;
        total_accounts++;
        accounts = accounts->next;
      } else if (accounts->locked == true) {
        accounts = accounts->next;
      } else {
        accounts = accounts->next;
      }
    }
  }
  if (total_accounts == 0) {
    return zero;
  } else {
    average_balance = total_balance / total_accounts;
  }
  return average_balance;
}
long double getBankFunds(Record *accounts) {
  long double total_balance = 0.0;
  if (accounts == NULL) {
    return total_balance;
  } else {
    while (accounts != NULL) {
      if (accounts->locked == false) {
        total_balance = total_balance + accounts->balance;
        accounts = accounts->next;
      } else if (accounts->locked == true) {
        accounts = accounts->next;
      } else {
        accounts = accounts->next;
      }
    }
  }
  return total_balance;
}
void closeBank(Record *accounts) {
  if (accounts == NULL) {
    return;
  }
  Record *t = accounts;
  while (accounts != NULL) {
    t = accounts->next;
    delete accounts;
    accounts = t;
  }
}
}  // namespace BankManagementSystem
}  // namespace ICS45C