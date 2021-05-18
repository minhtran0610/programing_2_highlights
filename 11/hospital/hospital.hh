/* Class Hospital
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a hospital. Only a single object created from this
 * class. Implements all commands in hospital program.
 *
 * Note: Students need change this class to implement commands missing
 * in the template code.
 *
 * The class Hospital carries out the main commands for the program.
 * The methods which are added and the corresponding commands:
 *  - enter(params): ENTER <patient_id>: Add a new patient to the database
 *  - leave(params): LEAVE <patient_id>: Remove a patient from the databse
 *  - assign_staff(params): ASSIGN_STAFF <specialist_id> <patient_id>:
 * Assign a staff to the patient's recurring care period
 *  - print_patient_info(params): PRINT_PATIENT_INFO <patient_id>:
 * Print the info of care periods and medicines of a patient
 *  - print_care_periods_per_staff(params): PRINT_CARE_PERIODS <specialist_id>:
 * Print the care periods that a specialist is assigned to
 *  - print_all_medicines(): PRINT_ALL_MEDICINES: print all the medicines
 * and the patients that are prescribed with that medicine
 *  - print_all_patients(): PRINT_ALL_PATIENTS: print all the patients that
 * has been in the hospital and their care periods
 *  - print_current_patients(): PRINT_CURRENT_PATIENTS: print the patients that
 * are currently in the hospital and their care periods
 *
 * Student: Minh Tran
 * Student ID: 50359358
 * Email: minh.s.tran@tuni.fi
 * */
#ifndef HOSPITAL_HH
#define HOSPITAL_HH

#include "person.hh"
#include "careperiod.hh"
#include "date.hh"
#include "utils.hh"
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>

// Error and information outputs
const std::string ALREADY_EXISTS = "Error: Already exists: ";
const std::string NOT_NUMERIC = "Error: Wrong type of parameters.";
const std::string CANT_FIND = "Error: Can't find anything matching: ";
const std::string STAFF_RECRUITED = "A new staff member has been recruited.";
const std::string PATIENT_ENTERED = "A new patient has entered.";
const std::string PATIENT_LEFT = "Patient left hospital, care period closed.";
const std::string MEDICINE_ADDED= "Medicine added for: ";
const std::string MEDICINE_REMOVED= "Medicine removed from: ";
const std::string STAFF_ASSIGNED= "Staff assigned for: ";

using Params = const std::vector<std::string>&;

class Hospital
{
public:
    // Constructor.
    Hospital();

    // Destructor.
    ~Hospital();

    // Recruits a new staff member (creates a new person object).
    void recruit(Params params);

    // Adds a patient in the hospital and creates a new care period.
    // If the person given as a parameter has never visited hospital earlier,
    // creates a new person object, otherwise just adds an existing person
    // in the newly created care period.
    void enter(Params params);

    // Removes the person given as a parameter from the hospital, and closes
    // person's care period.
    // However, the care period still exists.
    void leave(Params params);

    // Assigns the given staff member for the given patient.
    // If the patient already has the staff member assigned
    // (in the current care period), nothing happens.
    void assign_staff(Params params);

    // Adds the given medicine (name, strength, dosage) for the given patient.
    // If the given patient already has the medicine,
    // the prescription (strength, dosage) possibly changes.
    // If the given patien already has the medicine with same prescription,
    // nothing happens.
    void add_medicine(Params params);

    // Removes the given medicine from the patient.
    // If the patient does not have the medicine, nothing happens.
    void remove_medicine(Params params);

    // Prints the given patient's medicines.
    //void print_patient_medicines(Params params); // ei käytössä

    // Prints the given patient's all care periods and their current medicines,
    // i.e. those that have been added but not removed.
    void print_patient_info(Params params);

    // Prints the patients of the given staff member, i.e. those patients whose
    // care periods the given staff member has worked in.
    //void print_patients_per_staff(Params params); // ei käytössä

    // Prints the care periods of the given staff member, i.e. those
    // care periods the given staff member has worked in.
    void print_care_periods_per_staff(Params params);

    // Prints all medicines that are used by some patient visited the hospital
    // at some time, i.e. all medicines of current and earlier patients.
    void print_all_medicines(Params);

    // Prints all staff recruited in hospital.
    void print_all_staff(Params);

    // Prints all patients visited the hospital at some time, i.e. all
    // current and earlier patients.
    // More precisely, prints each patient's id and patient info
    // (in the same format as the method print_patient_info).
    void print_all_patients(Params);

    // Prints all patients currently in hospital at some time.
    // More precisely, prints each patient's id and patient info
    // (in the same format as the method print_patient_info).
    void print_current_patients(Params);

    // Sets a new value for the current date.
    void set_date(Params params);

    // Advances the current date with the given number of days.
    void advance_date(Params params);

private:
    // Obvious container attributes.
    std::map<std::string, Person*> current_patients_;
    std::map<std::string, Person*> staff_;

    // More attributes and methods
    // A map to store the patients who has left the hospital
    std::map<std::string, Person*> all_patients_;

    // A database to store the care periods
    std::map<std::string, std::vector<std::shared_ptr<CarePeriod>>> care_periods_;

    // Private comparison method to compare the starting date of the care periods
    static bool compare_start_date(std::shared_ptr<CarePeriod> care_period_1,
                                   std::shared_ptr<CarePeriod> care_period_2);

    // Get all medicines from all the patients, and return a map that has
    // the medicines as the keys and the vector of patients who are
    // prescribed with that medicine as the value
    std::map<std::string, std::set<std::string>> get_all_medicines();

    // Print the information of the patients according to the database given by
    // the user. This is used for print_all_patients and print_current_patients
    // because they are basically the same
    void print_patients(std::map<std::string, Person*> database);
};

#endif // HOSPITAL_HH
