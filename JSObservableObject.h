//
//  JSObservableObject
//  Copyright (c) John Sundell 2014
//

#import <Foundation/Foundation.h>

/**
 *  Create a JSObservableObject subclass @interface with an observation protocol
 *
 *  @param className The name the subclass should have
 *  @param protocol The protocol that observers must implement
 
 *  @discussion Use this macro to make any Objective-C class observable with a
 *  observation protocol. Call it instead of declaring your class' @interface
 *  manually. Like this:
 *
 *  JSObservableObjectInterface(MyClass, MyClassObserver)
 *
 *  // Your methods here
 *
 *  @end
 *
 *  That will add the following two methods to your class' interface:
 *
 *  - addObserver: Adds an observer to the object
 *  - removeObserver: Removes an observer from the object
 *
 *  The methods are already implemented in JSObservableObject, so no additional
 *  setup is required.
 */
#define JSObservableObjectInterface(className, observerProtocol) @protocol JSObservableObject_className @optional -(void)addObserver:(id<observerProtocol>)observer; -(void)removeObserver:(id<observerProtocol>)observer; @end @interface className : JSObservableObject <JSObservableObject_className> @end @interface className()

/**
 *  A class that makes it easy to add protocol-based observation to any class
 */
@interface JSObservableObject : NSObject

/**
 *  Whether instances of this class should retain its observers
 *
 *  @discussion Defaults to NO
 */
+ (BOOL)shouldRetainObservers;

/**
 *  Notify this object's observers of an event
 *
 *  @param selector The selector to send to this object's observers.
 *  @param parameters The parameters to send with the selector. This array must contain
 *  the same amount of objects as the selector has parameters.
 */
- (void)notifyObserversWithSelector:(SEL)selector parameters:(NSArray *)parameters;

@end