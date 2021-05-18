/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 *
 * The class CarePeriod resembles a single care period of a patient in the
 * hospital.
 *
 * The attributes of the class stores the basic information of a care period:
 *  - The patient who owns the care period
 *  - Start & end date
 *  - List of staff who is assigned to the care period
 *  - Status of the care period (is it closed?)
 *
 * The methods of the class can:
 *  - Get the patient ID and the start date of the care period
 *  - Check if the period is closed and close the period
 *  - Add a new specialist who is assigned for the care period and
 * check if a staff is assigned to this period
 *  - Print the dates and patients or staff of the period
 *
 * Student: Minh Tran
 * Student number: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>
#include <set>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods
    // Getters
    std::string get_patient_id() const;
    Date get_start_date() const;

    // Check if a period is closed
    bool is_closed();

    // Close an occuring period, e.g, add an end date to the object and
    // change is_closed_ to true
    void close_period(const Date& end);

    // Add staff to the care period
    void add_staff(std::string specialist_id);

    // Print the information of a single care period for a patient
    // E.g. print the information of the date and staff of the period
    void print_care_period_for_patient();

    // Print the information of a single care period for staff
    // e.g. print the information of the date and patient of the period
    void print_care_period_for_staff();

    // Check if a staff is assigned to the care period
    bool has_staff(std::string specialist_id);

private:
    Person* patient_;
    Date start_;
    Date end_;

    // More attributes and methods
    // A set to store the staff that has been assigned to this period
    std::set<std::string> staff_;

    // A boolean attribute to check if the period is closed or not
    bool is_closed_;

    // Print the start and (possibly) the end date of the period
    void print_dates();

    // Print the staff of the care period
    void print_staff();
};

#endif // CAREPERIOD_HH
