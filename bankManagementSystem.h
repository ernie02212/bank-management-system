/******************************
 **  DO NOT CHANGE THIS FILE **
 ******************************
 * Your submission should implement the function prototypes described here.
 * Nothing in this file should be changed, nor does it need to be.
 * Any changes to this file will be discarded if you submit it to gradescope!
 */

#ifndef __BANK_MANAGEMENT_SYSTEM_H__
#define __BANK_MANAGEMENT_SYSTEM_H__

#include <string>

namespace ICS45C {
namespace BankManagementSystem {

typedef struct Record {
  bool locked;          // is this record locked
  double balance;       // amount of money in the account
  std::string phone;    // customer phone number
  std::string email;    // customer email address
  std::string fname;    // customer first name
  std::string lname;    // customer last name
  unsigned int id;      // customer account id
  struct Record *next;  // pointer to the next record
} Record;

/** openAccount
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *   - string fname: first name of the client
 *   - string lname: last name of the client
 *   - string email: email of the client
 *   - string phone: phone number of the client
 *
 * Functionality:
 *   1. create a new account with the given information
 *     - the id of the account should be auto-increasing
 *       - first account's ID is 0, second account 1, and so on.
 *     - initial balance should be 0.0
 *     - this account should start unlocked
 *   2. add this account to the *end* of the linked list
 *
 * Return:
 *   - Record*: the (possibly new) head of the linked list.
 */
Record *openAccount(Record *accounts, std::string fname, std::string lname,
                    std::string email, std::string phone);

/** lockAccount
 * Params:
 *   - Record *account: pointer to a single account we want to lock
 *
 * Functionality:
 *   1. update the given account to be locked
 *
 * Return:
 *   - None
 */
void lockAccount(Record *account);

/** unlockAccount
 * Params:
 *   - Record *account: pointer to a single account we want to unlock
 *
 * Functionality:
 *   1. update the given account to be unlocked
 *
 * Return:
 *   - None
 */
void unlockAccount(Record *account);

/** searchAcount
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *   - string field: indicates what field of the struct we want to match
 *   - string keyword: term we're searching in the indicated field
 *
 * Functionality:
 *   1. Check if field is one of: "ID", "FIRST", "LAST", "PHONE", or "EMAIL"
 *   2.1. If not, stop here
 *   2.2. If yes, we will search for the account that matches that field
 *   3. Go through all accounts and:
 *   4.1. check if account is unlocked
 *   4.2. check if account.[field] is equal to [keyword]
 *   5. if both (4.1) and (4.2) are true, we found the account we want!
 *
 * Return:
 *  - Record*:
 *      - if account was found, pointer to the account we're looking for.
 *      - if account was NOT found, return a nullptr
 */
Record *searchAccount(Record *accounts, std::string field, std::string keyword);

/** printDetails (v1)
 * Params:
 *   - Record *account: pointer to a single account we want to display
 *
 * Functionality:
 *   - Create a string with the account details using the following formats.
 *      1. If the account does not exist:
 *      |------
 *      |Account UNKNOWN
 *      |------
 *      |Sorry, this account does not exist.
 *      |------
 *
 *      2. If the account is locked:
 *      |------
 *      |Account #[ID]
 *      |------
 *      |Sorry, this account has been locked.
 *      |------
 *
 *      3. If the account is unlocked:
 *      |------
 *      |Account #[ID]
 *      |------
 *      |Status: OPEN
 *      |Account holder: [FIRST NAME] [LAST NAME]
 *      |Contact: [PHONE] / [EMAIL]
 *      |Balance: [BALANCE]
 *      |------
 *
 *   - in the format above, | indicates the start of a new line in the string
 *   - for the balance, you should use two decimal places
 *     - ref: https://stackoverflow.com/a/29200671
 *
 * Return:
 *  - string: a string containing the account's details in the format above
 */
std::string printDetails(Record *account);

/** printDetails (v2)
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *   - unsigned int id: ID of the account we want to display
 *
 * Functionality:
 *   - Create a string with the account details using the following formats.
 *      1. If the account does not exist:
 *      |------
 *      |Account UNKNOWN
 *      |------
 *      |Sorry, this account does not exist.
 *      |------
 *
 *      2. If the account is locked:
 *      |------
 *      |Account #[ID]
 *      |------
 *      |Sorry, this account has been locked.
 *      |------
 *
 *      3. If the account is unlocked:
 *      |------
 *      |Account #[ID]
 *      |------
 *      |Status: OPEN
 *      |Account holder: [FIRST NAME] [LAST NAME]
 *      |Contact: [PHONE] / [EMAIL]
 *      |Balance: [BALANCE]
 *      |------
 *
 *   - in the format above, | indicates the start of a new line in the string
 *   - for the balance, you should use two decimal places
 *     - ref: https://stackoverflow.com/a/29200671
 *
 * Return:
 *  - string: a string containing the account's details in the format above
 */
std::string printDetails(Record *accounts, unsigned int id);

/** updateAccount (v1)
 * Params:
 *   - Record *account: pointer to a single account we want to modify
 *   - string firstName: new first name for the customer in this account
 *   - string lastName: new first name for the customer in this account
 *   - string phone: new first name for the customer in this account
 *   - string email: new first name for the customer in this account
 *   - bool locked: new locked status for this account
 *
 * Functionality:
 *   1. Change all fields in the account with the new data
 *
 * Return:
 *  - None
 */
void updateAccount(Record *account, std::string firstName, std::string lastName,
                   std::string phone, std::string email, bool locked);

/** updateAccount (v2)
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *   - unsigned int id: ID on the account we want to modify
 *   - string firstName: new first name for the customer in this account
 *   - string lastName: new first name for the customer in this account
 *   - string phone: new first name for the customer in this account
 *   - string email: new first name for the customer in this account
 *   - bool locked: new locked status for this account
 *
 * Functionality:
 *   1. Find the account with the given ID
 *   2. Change all fields in the account with the new data
 *
 * Return:
 *  - None
 */
void updateAccount(Record *accounts, unsigned int id, std::string firstName,
                   std::string lastName, std::string phone, std::string email,
                   bool locked);

/** deposit (v1)
 * Params:
 *   - Record *account: pointer to a single account we want to deposit to
 *   - double value: amount of money to be added
 *
 * Functionality:
 *   1. Check if the account is unlocked; if not, return -123.45
 *   2. Check if value is >= 0
 *   3.1. value >= 0: Increase the account's balance by [value]
 *   3.2. value < 0: Do not change the balance in the account
 *
 * Return:
 *   - double:
 *     - if account is unlocked: the updated balance on the account
 *     - if account doesn't exist or it is locked: -123.45
 */
double deposit(Record *account, double value);

/** deposit (v2)
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *   - unsigned int id: ID of the account we want to add cash
 *   - double value: amount of money to be added
 *
 * Functionality:
 *   1. Find the account with the corresponding ID
 *   2. Check if the account is unlocked; if not, return -123.45
 *   3. Check if value is >= 0
 *   4.1. value >= 0: Increase the account's balance by [value]
 *   4.2. value < 0: Do not change the balance in the account
 *
 * Return:
 *   - double:
 *     - if account is unlocked: the updated balance on the account
 *     - if account doesn't exist or it is locked: -123.45
 */
double deposit(Record *accounts, unsigned int id, double value);

/** withdrawal (v1)
 * Params:
 *   - Record *account: pointer to a single account we want to withdraw from
 *   - double value: amount of money to be withdrawn
 *
 * Functionality:
 *   1. Check if the account is unlocked; if not, return -123.45
 *   2. Check if value is >= 0
 *   3.1. value >= 0: Decrease the account's balance by [value]
 *   3.2. value < 0: Do not change the balance in the account
 *
 * Return:
 *   - double:
 *     - if account is unlocked: the updated balance on the account
 *     - if account doesn't exist or it is locked: -123.45
 */
double withdrawal(Record *account, double value);

/** withdrawal (v2)
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *   - unsigned int id: ID of the account we want to withdraw money from
 *   - double value: amount of money to be withdrawn
 *
 * Functionality:
 *   1. Find the account with the corresponding ID
 *   2. Check if the account is unlocked; if not, return -123.45
 *   3. Check if value is >= 0
 *   4.1. value >= 0: Decrease the account's balance by [value]
 *   4.2. value < 0: Do not change the balance in the account
 *
 * Return:
 *   - double:
 *     - if account is unlocked: the updated balance on the account
 *     - if account doesn't exist or it is locked: -123.45
 */
double withdrawal(Record *accounts, unsigned int id, double value);

/** deleteAccount
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *   - unsigned int id: ID of the account we want to delete
 *
 * Functionality:
 *   1. look for the account with the matching ID
 *   2. if found, delete that record and fix pointers
 *
 * Return:
 *   - Record*: the (possibly new) head of the linked list.
 */
Record *deleteAccount(Record *accounts, unsigned int id);

/** countUnlockedAccounts
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *
 * Functionality:
 *  1. Count how many accounts in the list are unlocked
 *
 * Return:
 *  - unsigned int: the count of valid (i.e., unlocked) accounts
 */
unsigned int countUnlockedAccounts(Record *accounts);

/** countLockedAccounts
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *
 * Functionality:
 *  1. Count how many accounts in the list are locked
 *
 * Return:
 *  - unsigned int: the count of locked accounts
 */
unsigned int countLockedAccounts(Record *accounts);

/** countAllAccounts
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *
 * Functionality:
 *  1. Count how many accounts are in the list
 *
 * Return:
 *  - unsigned int: the count of all created accounts (both locked and unlocked)
 */
unsigned int countAllAccounts(Record *accounts);

/** getAverageBalance
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *
 * Functionality:
 *  1. Calculate the average of the balances of all unlocked accounts
 *
 * Return:
 *  - long double: the average of the balances of all unlocked accounts
 */
long double getAverageBalance(Record *accounts);

/** getBankFunds
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *
 * Functionality:
 *  1. Calculate the sum of the balances of all unlocked accounts
 *
 * Return:
 *  - long double: the sum of the balances of all unlocked accounts
 */
long double getBankFunds(Record *accounts);

/** closeBank
 * Params:
 *   - Record *accounts: pointer to head of linked list with created accounts
 *
 * Functionality:
 *  1. delete all created accounts and free all used memory
 *
 * Return:
 *  - None
 */
void closeBank(Record *accounts);

}  // namespace BankManagementSystem
}  // namespace ICS45C

#endif  // __BANK_MANAGEMENT_SYSTEM_H__