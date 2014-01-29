#import "JSObservableObject.h"

@interface JSObservableObject()

@property (nonatomic, strong) NSHashTable *observers;

@end

@implementation JSObservableObject

+ (BOOL)shouldRetainObservers
{
    return NO;
}

- (void)addObserver:(id)observer
{
    if (!self.observers) {
        NSHashTableOptions hashTableOptions;
        
        if ([[self class] shouldRetainObservers]) {
            hashTableOptions = NSHashTableStrongMemory;
        } else {
            hashTableOptions = NSHashTableWeakMemory;
        }
        
        self.observers = [NSHashTable hashTableWithOptions:hashTableOptions];
    } else if ([self.observers containsObject:observer]) {
        return;
    }
    
    [self.observers addObject:observer];
}

- (void)removeObserver:(id)observer
{
    [self.observers removeObject:observer];
}

- (void)notifyObserversWithSelector:(SEL)selector parameters:(NSArray *)parameters
{
    for (id observer in self.observers) {
        if (![observer respondsToSelector:selector]) {
            continue;
        }
        
        NSMethodSignature *methodSignature = [observer methodSignatureForSelector:selector];
        NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:methodSignature];
        invocation.target = observer;
        invocation.selector = selector;

        for (NSUInteger i = 0; i < [parameters count]; i++) {
            id parameter = [parameters objectAtIndex:i];
            
            [invocation setArgument:&parameter
                            atIndex:i + 2];
        }
        
        [invocation invoke];
    }
}

@end