#include "queue.hh"

// Implement the member functions of Queue here

// Constructor
Queue::Queue(unsigned int cycle): cycle_(cycle) {};

// Destructor
Queue::~Queue() {
    while (first_ != nullptr) {
        Vehicle* vehicle_to_be_deleted = first_;
        first_ = first_->next;

        delete vehicle_to_be_deleted;
    }
}

// Insert a vehicle with the given register number to the queue
void Queue::enqueue(string reg) {
    if (not is_green_) {
        Vehicle* vehicle_to_be_added = new Vehicle{reg, nullptr};

        if (first_ == nullptr) {
            first_ = vehicle_to_be_added;
            last_ = vehicle_to_be_added;
        } else {
            last_->next = vehicle_to_be_added;
            last_ = vehicle_to_be_added;
        }
    } else {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    }
}

// Print the queue of vehicles waiting
void Queue::print() {
    if (first_ == nullptr) {
        if (is_green_) {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
        } else {
            cout << "RED: No vehicles waiting in traffic lights" << endl;
        }
    } else {
        if (not is_green_) {
            string car_string = "";

            Vehicle* current = first_;
            while (current != nullptr) {
                car_string += (current->reg_num + ' ');
                current = current->next;
            }
            cout << "RED: Vehicle(s) " << car_string << "waiting in traffic lights" << endl;
        } else {
            cout << "Error!" << endl;
        }
    }
}

// Change the cycle of the queue
void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

// Remove a car from the queue when the lights turn green
bool Queue::dequeue(string& reg) {
    if (first_ == nullptr) {
        return false;
    } else {
        Vehicle* vehicle_to_be_moved = first_;
        reg = vehicle_to_be_moved->reg_num;

        first_ = first_->next;
        delete vehicle_to_be_moved;
        return true;
    }
}

// Switch the lights and let the vehicles go through the light
void Queue::switch_light() {
    if (first_ == nullptr) {
        if (is_green_) {
            is_green_ = false;
        } else {
            is_green_ = true;
        }
        print();
    } else {
        if (not is_green_) {
            string car_string = "";
            for (unsigned int i = 0; i < cycle_; i++) {
                string car_reg = "";
                if (dequeue(car_reg)) {
                    car_string += (car_reg + " ");
                }
            }
            cout << "GREEN: Vehicle(s) " << car_string << "can go on" << endl;
        } else {
            cout << "Error!" << endl;
        }
    }
}
