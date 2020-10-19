/**
 * @file mainpage.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Bus System Visualization Simulator
 *
 * \section intro_sec Introduction
 *
 * This is a simulation of a transit system that examines buses, routes, and
 * and stops around the U of M campus.
 * The code for the transit simulation can be found at:
 * https://github.umn.edu/umn-csci-3081-s20/repo-rosss001/tree/master/project
 *
 * The code must be run on a CSE labs machine.
 * It uses the CSE network to display the simulation on a website.
 *
 * To compile the code, navigate to the /src directory and make.
 * Then change directories to the project main directory, and type:
 *
 * ./build/bin/vis_sim <port_number>
 *
 * The port number is a 4 digit number above 8000, where the last three
 * digits are identical to the last 3 digits of your student id number.
 *
 * After the executable is run, open a browser and navigate to:
 * http://127.0.0.1:<port_number>/web_graphics/project.html
 * where the port number is the same as used when executing the system.
 *
 * That webpage will show the simulation visualized. The Start button will
 * begin the simulation, and the Pause button will pause the simulation.
 * The sliders will change the time step and step intervals of the sim.
 *
 * /sec bus_fact_sec Bus Factory Implementation
 *
 * Unfortunately, I was not able to properly implement a Bus Factory into the
 * system. However, the plan that I was intending to use was a concrete factory.
 * A concrete has the benefit of needing less extra classes than an abstract
 * factory. A concrete factory will have a higher cohesion, containing all of
 * the necessary methods in one class. It will also have less coupling than
 * an abstract factory, as there are fewer classes overall. This gives the
 * advantage of more straight forward to read code. The code can be presented
 * in a simple way, which can make it more readable. This is highly important
 * when working in the middle of a system. In the case such as this project,
 * where the task is to extend an already existing system, it is helpful
 * to be aware of the relatively large code base that already exists in the
 * project. Simplifying things can be of a big benefit.
 *
 * The negative of a concrete factory is that it is harder to extend later on.
 * The concrete factory does an adequate job of creating one object to be used.
 * The objects that the factory create have inheritance from the initial object,
 * which is the Bus class in this case. This inheritance is helpful, but can
 * also backfire on the factory if it is changed in the future. If the class
 * that is being extended for the factory is changed in a meaningful way,
 * the factory will also need to undergo some changes to match it. A concrete
 * factory works well in the situation where you don't need many types of an
 * object, and you don't anticipate that number to grow after the initial
 * implementation.
 *
 * The other option would have been to make an abstract bus factory. An abstract
 * factory is a good implementation of the open/closed principle of object
 * oriented programming. The abstract factory creates new, individual classes
 * for each type of bus that is to be created. This is ideal for the open/closed
 * principle, because these classes don't need to be modified after they are
 * complete. Along with the fact that if another bus size needed to be added
 * at some point, it would be as simple as adding another factory that extends
 * the initial abstract class.
 *
 * The draw back to an abstract factory implementation is that it can become
 * confusing. It creates a much higher coupling factor, because all of the
 * different subclasses will be self contained units. This can make things
 * harder to view and understand, potentially. It is on the programmer to make
 * sure the documentation is very clear as to how the factory works and how the
 * pieces fit together. Ultimately, in my opinion, an abstract factory is best
 * for when you need to be creating many different types of an object. In the
 * case that you need many different types of an object, an abstract Factory
 * handles that in a straightforward way, even if the end result is slightly
 * more confusing.
 *
 * /sec observer_sec Observer Pattern Implementation
 *
 * The observer pattern implemented in this system uses a specific observer
 * class to check the buses in the simulation. The Bus class was changed to
 * inherit from a newly create IObservable class. This IObservable class
 * contained the necessary methods to let the Bus class, which is now an
 * extended IObservable object, clear, add, and notify the observers that are
 * keeping track of it. All of the methods were implemented in the IObservable
 * class itself. The only change that needed to be made to the Bus class was
 * an added call to NotifyObservers() within the Bus's Update() function. This
 * function is when all updates to the bus data are finalized, so it made sense
 * to also notify any observers of changes in this location.
 *
 * A separate class called IObserver was also created. This class was purely
 * virtual, and another class, BusWebObserver, was created that inherited it.
 * This BusWebObserver class has objects created every time a new observer is
 * created. In this implementation of the simulation, only one observer can be
 * created at a time. The BusWebObserver uses the bus_data that is sent to it
 * by the bus it is observing to print out important information on the bus.
 *
 * The other major part of the observer in this system is the web interface.
 * There are three parts that need to work together to make the server-side
 * view of the observer possible. Specifically, the bus data is printed on the
 * screen using the sketch.js file, the interaction with the sketch.js is
 * handled by the my_web_server_command classes, and the interaction with the
 * overall system is handled by the visualization_simulator class. Provided to
 * us was the sketch.js file, which already had all of the relvant and necessary
 * changes needed to display the object information. The BusWebObserver, which
 * was also provided to us, interacts with the web server to print the
 * information. In the my_web_server_command classes, functionality is added
 * to handle the input from the server. This interaction from the user is
 * handled first by the sketch.js file, which then sends it to the
 * my_web_server_command relevant classes. Those classes then interact with
 * the newly added visualization_simulator methods, being AddListener() and
 * ClearListeners(). These classes maintain how the rest of the system handles
 * the observer information. AddListener() adds an observer to the Bus object
 * that is to be observed, and ClearListeners() clears any observers off of all
 * Bus objects that exist in the system.
 *
 * The observer system provides a very useful way to check information and
 * results of the simulation without scrolling through many lines of output.
 * The ability to check quickly on one bus and the information it holds
 * can show many things. It can show that passenngers are being generated,
 * albeit not necessarily following the randomness desired. The observer
 * can also check on buses that are created to make sure their capacity is
 * correctly following the newly implemented strategy that exists in the bus
 * factory. With some small tweaks, it will also be easy to change the current
 * observable and observer classes into template classes, which will allow
 * the observation of more than just buses. Future iterations of the project
 * will probably pull on this task.
 *
 * There was not much difficulty in implementing the bus observer. There were
 * a few tricky things that were missed initially, but easy to fix when found.
 * The hardest part of the implementation was when I attempted to split the
 * BusWebObserver class from the my_web_server_command.cc file, which seems like
 * a file in which it does not belong. However, given the time constraints and
 * somewhat frustrating linking issues that were created by this, ultimately I
 * added it back tot he my_web_server_command.cc file, and the observer runs
 * as expected. The observer.cc file that was provided in lecture and was part
 * of a out-of-class exercise was very helpful to both understand the observer
 * pattern and in implementing the pattern in this system.
 *
 * /sec decorator_sec Designing and Implementing the Decorator Pattern
 *
 * The Decorator Pattern is a design pattern that puts emphasis on enclosing
 * classes in "decorator" classes to alter them in ways that do not modify the
 * base class. This pattern has a lot of applications across the field of
 * programming, as it allows for very extensible code that does not have an
 * impact on the base code. The implementation in this system is as a cosmetic
 * change, but that is not the only way it can be used.
 *
 * The pattern that I have implemented uses a high amount of coupling to connect
 * all of the different classes. To decorate the buses, a class is created
 * as an interface for buses that is pure virtual. Both the normal bus class
 * and a newly created decorator class utilize this bus interface. This allows
 * the bus decorator to access all of the normal bus methods, and modify only
 * the ones that are required for decoration. The bus decorator class then has
 * further classes that modify the base bus in only one specific way. In this
 * case, that is changing the bus's color or the intensity of the color the bus
 * has.
 *
 * In practice, this is achieved by 'wrapping' the bus objects in the decorator
 * objects. After a bus is created, a general decorator object is created using
 * the base bus as the basis for its constuctor. After that, the color and
 * intensity decorators can be created as objects which use this general
 * decorator as their basis for construction. One of the big benefits of this
 * system is that the specific decorators can actually decorate other decorator
 * objects; this means that a Gold Color decorator can 'decorate' a Maroon Color
 * decorator with no issues arising. The way that I have implemented the code,
 * by checking if the exisiting color is black, allows for the decoration of
 * objects in exactly the way I want them to be decorated. On top of a color
 * decorating another color, and even more useful, is that the Intensity
 * decorator can modify any of the other objects, too. As the bus objects gains
 * or loses passengers throughout the simulation, the intensity of the color
 * that the bus is currently presented as increases or decreases accordingly.
 * This makes for a very nice and fluid looking system that is much more
 * intersting to look at then the plain white objects moving across the screen.
 *
 * Another way that the Decorator Pattern could have been used in this system
 * is to 'decorate' the stops in a non-visual way. Stops populated by
 * passengers, which are moved to buses when a bus arrives. Instead of keeping
 * a vector of passengers in the Stop object, the Stop object could be
 * 'decorated' with passenger objects wrapping around it. When a bus 'picks up'
 * the passengers, all of the passenger wrappers are taken off the stop and
 * added to the bus. This is not necessarily a better way to implement this
 * functionality, but an example of how the decorator pattern is not simply
 * for cosmetic problems. Any situation where a base class does not want to be
 * changed by some modification is potentially suitable for the decorator
 * pattern.
 *
 * My implementation of the decorator pattern is one that focuses heavily on
 * coupling, at the cost of cohesion. Along with the normal Bus class, I
 * have added a BusInterface, BusDecorator, GoldDecorator, MaroonDecorator,
 * and an IntensityDecorator. Both Bus and BusDecorator inherit from the
 * BusInterface, and the other three Decorators inherit from BusDecorator.
 * This means all of objects that are created are essentially of the type of
 * the BusInterface, meaning they all have access to the Interface's classes.
 * This is what allows the decorators to access elements of the bus - they
 * simply edit one aspect of the bus object, and let the Bus class do all
 * of the rest of the heavy lifting. This makes for extensible code, as well.
 * If another color were to be added, it would be as simple as creating a new
 * decorator class (which is as simple as copying the BusDecorator class), and
 * then just modifying the one aspect that is desired. If a special color
 * was desired for a holiday or special event, a quick copy and addition to the
 * code fixes it up.
 *
 * The drawback to this method is that the code has low cohesion. If I want to
 * add a method to the Bus class, I have to add it to all other members of the
 * family for the implementation to continue working properly. This can be
 * tedious and tricky, because instead of adding method to one class, it now
 * needs to be added to 5 classes (and more if other colors were added). The
 * balance between coupling and cohesion is one that every programmer weighs
 * when creating their systems, as there is no right answer.
 *
 * Another way to implement the decorator pattern would be to have created
 * a child class of Bus. Rather than creating an interface that the decorators
 * also inherit from, having the decorator inherit from Bus is a possibility.
 * This leads to more cohesive code, but also lowers the coupling. It also
 * limits the ability of decorators to wrap one another, and leads itself
 * to handling all decoration just in the one Decorator class. The Bus class
 * is still wrapped and protected, but an extension of the decoration may be
 * harder to implement.
 *
 * For this system, this example of a single inheritance would have been a lot
 * easier to implement than the more extensible version that I did implement.
 * The one decorator class that inherits from Bus would not need to alter or
 * change any aspect of the Bus that it doesn't touch, in the same way that
 * exists now. This method also allows for better encapsulation if needed,
 * because the child class could inherit protected methods/fields if needed.
 * That was not an issue for this system, but it is worth pointing out.
 *
 * Ultimately, the Decorator Pattern was unnecessary for this system. Creating
 * all the excess classes and inheritance was needlessly complex. I was able
 * to implement the same functionality in just the Bus class with about 5 lines
 * code. It could require more work to extend if desired, but with a simple task
 * like this, a simple solution may be the correct one.
 */

#endif  // SRC_MAINPAGE_H_
