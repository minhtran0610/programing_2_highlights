#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
    is_closed_ = false;
}


CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
    is_closed_ = false;
}


CarePeriod::~CarePeriod()
{
}


std::string CarePeriod::get_patient_id() const {
    return patient_->get_id();
}


Date CarePeriod::get_start_date() const {
    return start_;
}


bool CarePeriod::is_closed() {
    return is_closed_;
}


void CarePeriod::close_period(const Date& end) {
    end_ = end;
    is_closed_ = true;
}


void CarePeriod::add_staff(std::string specialist_id) {
    staff_.insert(specialist_id);
}


void CarePeriod::print_care_period_for_patient() {
    // Print the dates of the care period
    std::cout << "* Care period: ";
    print_dates();
    std::cout << std::endl;

    // Print the staff of the care period
    std::cout << "  - Staff: ";
    print_staff();
    std::cout << std::endl;
}


void CarePeriod::print_care_period_for_staff() {
    // Print the dates of the care period
    print_dates();
    std::cout << std::endl;

    // Print the name of the patient
    std::cout << "* Patient: " << get_patient_id() << std::endl;
}


bool CarePeriod::has_staff(std::string specialist_id) {
    return (staff_.find(specialist_id) != staff_.end());
}


void CarePeriod::print_dates() {
    // Print the start date
    start_.print();
    std::cout << " -";

    // If the care period is closed, print the end date
    if (is_closed()) {
        std::cout << " ";
        end_.print();
    }
}


void CarePeriod::print_staff() {

    if (staff_.size() == 0) {
        std::cout << "None";
    } else {
        // Create a string of staff
        std::string staff_string = "";
        for (std::string specialist_id : staff_) {
            staff_string += (specialist_id + " ");
        }
        staff_string = staff_string.substr(0, staff_string.length()-1);

        // Print the string
        std::cout << staff_string;
    }
}
