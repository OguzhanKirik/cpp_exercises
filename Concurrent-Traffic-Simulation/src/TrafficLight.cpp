#include <iostream>
#include <random>
#include "TrafficLight.h"
#include <future>

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_queue.empty(); }); // pass unique lock to condition variable

    // remove last vector element from queue
    T msg = std::move(_queue.back());
    _queue.pop_back();

    return msg; // will not be copied due to return value optimization (RVO) in C++
}



template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    {
        // simulate some work

        // perform vector modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);

        // add vector to queue
        _queue.push_back(std::move(msg));
        _cond.notify_one(); // notify client after pushing new Vehicle into vector
    }
}









TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.`
    while (true)
    {
        std::this_thread::sleep_for( std::chrono::milliseconds(1) );

        auto cur_phase = msg_queue->receive();
        if (cur_phase == TrafficLightPhase::green)
            return;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    //std::unique_lock<std::mutex> lck(_mtx);
    threads.emplace_back( std::thread(&TrafficLight::cycleThroughPhases, this) );
    //lck.unlock();

}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 

    std::random_device rd;
    std::mt19937 eng( rd() );
    std::uniform_int_distribution<> distribution(4, 6);


      // print id of the current thread
      std::unique_lock<std::mutex> lck(_mtx);
      std::cout << "Vehicle #" << TrafficObject::_id << "::drive: thread id = " << std::this_thread::get_id() << std::endl;
      lck.unlock();
      
      std::chrono::time_point<std::chrono::system_clock> lastUpdate;
      //init stop watch
      int cycle_duration = distribution(eng);

      lastUpdate = std::chrono::system_clock::now();
  
      while(true){
          std::this_thread::sleep_for((std::chrono::milliseconds(1)));
          long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
          if(timeSinceLastUpdate >= cycle_duration){
              // toggle phase
              if(_currentPhase == TrafficLightPhase::red){
                  _currentPhase = TrafficLightPhase::green;
              }else{
                  _currentPhase = TrafficLightPhase::red;
              }

            // Send update to the message queue and wait
            auto msg = _currentPhase;
            auto is_sent = std::async( std::launch::async, &MessageQueue<TrafficLightPhase>::send, msg_queue, std::move(msg) );
            is_sent.wait();


            // Randomly choose the cycle duration for the next cycle
            cycle_duration = distribution(eng);
        
            lastUpdate = std::chrono::system_clock::now();
          }
      }

}



