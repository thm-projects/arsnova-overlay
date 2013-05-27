#import <Foundation/Foundation.h>

NSAutoreleasePool * pool;

int startApplication(int argc, char ** argv) {
    NSLog(@"Start ArsNovaWidget");
    pool = [[NSAutoreleasePool alloc] init];
    return 0;
}

void stopApplication() {
    [pool release];
}
