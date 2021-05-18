#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}


Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for (std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter)
    {
        delete iter->second;
    }
}


void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}


void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);
    // Check if the patient ID already exists in the database
    if (current_patients_.find(patient_id) != current_patients_.end()) {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    // If the person has never entered the hospital, e.g. doesn't exists
    // in left patients database, create a new Person object for them
    Person* new_patient = nullptr;

    if (all_patients_.find(patient_id) == all_patients_.end()) {
        new_patient = new Person(patient_id);
        current_patients_.insert({patient_id, new_patient});
    } else {
        new_patient = all_patients_.at(patient_id);
        current_patients_.insert({patient_id, new_patient});
    }

    all_patients_.insert({patient_id, new_patient});

    // Print the message of the command
    std::cout << PATIENT_ENTERED << std::endl;

    // Create a new care period for the patient
    std::shared_ptr<CarePeriod> new_care_period(new CarePeriod(utils::today, new_patient));

    // Add the care period to the database
    if (care_periods_.find(patient_id) == care_periods_.end()) {
        care_periods_.insert({patient_id, {}});
        care_periods_[patient_id].push_back(new_care_period);
    } else {
        care_periods_[patient_id].push_back(new_care_period);
    }
}


void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);

    // Check if the patient is in the hospital or not
    if (current_patients_.find(patient_id) == current_patients_.end()) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Close the recurring care period and remove the patient from the database
    for (auto care_period : care_periods_[patient_id]) {
        if (not care_period->is_closed()) {
            care_period->close_period(utils::today);
            break;
        }
    }

    current_patients_.erase(patient_id);

    // Print the message
    std::cout << PATIENT_LEFT << std::endl;
}


void Hospital::assign_staff(Params params)
{
    std::string specialist_id = params.at(0);
    std::string patient_id = params.at(1);

    // Check if the staff is in the hospital
    if (staff_.find(specialist_id) == staff_.end()) {
        std::cout << CANT_FIND << specialist_id << std::endl;
        return;
    }

    // Check if the patient is currently in the hospital
    if (current_patients_.find(patient_id) == current_patients_.end()) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Assign staff to the patient's recurring care period
    for (auto care_period : care_periods_[patient_id]) {
        if (not care_period->is_closed()) {
            care_period->add_staff(specialist_id);
            break;
        }
    }

    std::cout << STAFF_ASSIGNED << patient_id << std::endl;
}


void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}


void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}


void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);

    // Check if the patient has never visited the hospital
    if (all_patients_.find(patient_id) == all_patients_.end()) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Print the information of care periods
    for (auto care_period : care_periods_[patient_id]) {
        care_period->print_care_period_for_patient();
    }

    // Print the medicine of the patient
    std::cout << "* Medicines:";
    Person* patient = all_patients_[patient_id];
    patient->print_medicines("  - ");
}


void Hospital::print_care_periods_per_staff(Params params)
{
    std::string specialist_id = params.at(0);

    // Check if the specialist can be found in the database
    if (staff_.find(specialist_id) == staff_.end()) {
        std::cout << CANT_FIND << specialist_id << std::endl;
        return;
    }

    // Get the care periods that this person is assigned to.
    // Save it to a vector
    std::vector<std::shared_ptr<CarePeriod>> care_periods_staff = {};

    for (auto item : care_periods_) {
        for (auto care_period : item.second) {
            if (care_period->has_staff(specialist_id)) {
                care_periods_staff.push_back(care_period);
            }
        }
    }

    // If the specialist hasn't been assigned to any vector, e.g. the
    // care period vector is empty, print "None". Else, print the
    // care period information
    if (care_periods_staff.size() == 0) {
        std::cout << "None" << std::endl;
    } else {
        // Sort the vector in chronological order
        std::sort(care_periods_staff.begin(), care_periods_staff.end(),
                  compare_start_date);
        // Print the care periods
        for (auto care_period : care_periods_staff) {
            care_period->print_care_period_for_staff();
        }
    }
}


void Hospital::print_all_medicines(Params)
{
    // Get the medicines from all patients
    std::map<std::string, std::set<std::string>> medicines_map = get_all_medicines();

    // If no medicine has been prescribed, e.g. the medicines map is empty,
    // print "None"
    if (medicines_map.empty()) {
        std::cout << "None" << std::endl;
        return;
    }

    // Print the information of the medicines and the patients who receive them
    for (auto iter : medicines_map) {
        std::cout << iter.first << " prescribed for" << std::endl;
        for (std::string patient_id : iter.second) {
            std::cout << "* " << patient_id << std::endl;
        }
    }
}


void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}


void Hospital::print_all_patients(Params)
{
    print_patients(all_patients_);
}


void Hospital::print_current_patients(Params)
{
    print_patients(current_patients_);
}


void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}


void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}


bool Hospital::compare_start_date(std::shared_ptr<CarePeriod> care_period_1,
                                  std::shared_ptr<CarePeriod> care_period_2) {
    if (care_period_1->get_start_date() == care_period_2->get_start_date()) {
        return care_period_1->get_patient_id() > care_period_2->get_patient_id();
    }
    return care_period_1->get_start_date() < care_period_2->get_start_date();
}


std::map<std::string, std::set<std::string>> Hospital::get_all_medicines() {
    // If there is no patient, return the empty map
    if (all_patients_.empty()) {
        return {};
    }

    // The map to store the result
    std::map<std::string, std::set<std::string>> result = {};

    // Get the medicines from each individual patient and insert the
    // information to the result map.
    std::vector<std::string> medicines;
    for (auto patient_pair : all_patients_) {
        medicines = patient_pair.second->get_medicines();
        for (std::string medicine : medicines) {
            if (result.find(medicine) == result.end()) {
                result.insert({medicine, {patient_pair.first}});
            } else {
                result[medicine].insert(patient_pair.first);
            }
        }
    }

    // Return the result map
    return result;
}


void Hospital::print_patients(std::map<std::string, Person *> database) {
    // If the databse for all the patients is empty, print "None"
    if (database.empty()) {
        std::cout << "None" << std::endl;
        return;
    }

    // Loop through the database to get the IDs of all patients.
    // Print the information of the patients using the IDs
    for (std::map<std::string, Person*>::iterator iter = database.begin();
         iter != database.end(); ++iter) {
        std::cout << iter->first << std::endl;
        std::vector<std::string> param = {iter->first};
        print_patient_info(param);
    }
}
