#import <Foundation/Foundation.h>

NSAutoreleasePool * pool;

int startApplication(int argc, char ** argv) {
    NSLog(@"Start ArsNovaWidget");
    pool = [[NSAutoreleasePool alloc] init];
}

void stopApplication() {
    [pool release];
}