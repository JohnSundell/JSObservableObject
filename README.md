JSObservableObject
==================

#### Easily add protocol-based observation to any Objective-C class

* No need to write manual observer implementations, just inherit from JSObservableObject and everything you need to for protocol-based observation will be setup for you.
* Protocol-based observation is much easier to maintain and less prone to silent failures than, for example, key value observation.
* Works with any existing observation protocols you might have.

#### Here's how to use JSObservableObject:

##### 1. Declare the protocol your observers must implement

```objective-c
@protocol MyClassObserver <NSObject>

- (void)myObject:(MyClass *)object didPerformTaskWithObject:(id)anotherObject;

@end
```

##### 2. Inherit from JSObservableObject using the JSObservableObjectInterface macro

```objective-c
#import "JSObservableObject.h"

JSObservableObjectInterface(MyClass, MyClassObserver)

@end
```

This will setup your class for observation, and require all observers to implement the `MyClassObserver` protocol.

##### 3. Objects can now call -addObserver: and -removeObserver: on instances of your class

```objective-c
MyClass *object = [MyClass new];
[object addObserver:self];

...

[object removeObserver:self];
```

#### 4. Notify observers of events

Use the `-notifyObserversWithSelector:parameters:` to notify your observers of an event. The selector should match a method declared in your observation protocol.

```objective-c
SEL selector = @selector(myObject:didPerformTaskWithObject:);
NSArray *parameters = @[self, anotherObject];

[self notifyObserversWithSelector:selector parameters:parameters];
```

The above code will send the specified selector to all of the object's observers, assigning the parameters as parameters to the call.

#### Hope that you'll enjoy using JSObservableObject!

Why not give me a shout on Twitter: [@johnsundell](https://twitter.com/johnsundell)