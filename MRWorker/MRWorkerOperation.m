//
//  MRWorkerTask.m
//  MRWorker
//
//  Copyright (c) 2013 Marc Ransome <marc.ransome@fidgetbox.co.uk>
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#import "MRWorkerOperation.h"

@interface MRWorkerOperation ()
{
    NSTask *_task;
    BOOL _executing;
    BOOL _finished;
    BOOL _waitingForTaskToExit;
    void (^outputCallback)(NSString *);
    void (^completionCallback)(int);
}

@end

@implementation MRWorkerOperation

- (instancetype)init
{
    if (self = [super init]) {
        _task = [[NSTask alloc] init];
    }
    
    return self;
}

- (instancetype) initWithLaunchPath:(NSString *)launchPath arguments:(NSArray *)arguments outputBlock:(void (^)(NSString *output))outputBlock completionBlock:(void (^)(int terminationStatus))completionBlock
{
    if (self = [super init]) {
        _task = [[NSTask alloc] init];
        [_task setLaunchPath:launchPath];
        if (arguments) {
            [_task setArguments:arguments];
        }
        outputCallback = outputBlock;
        completionCallback = completionBlock;
    }
    
    return self;
}

+ (instancetype)workerOperationWithLaunchPath:(NSString *)launchPath arguments:(NSArray *)arguments outputBlock:(void (^)(NSString *output))outputBlock completionBlock:(void (^)(int terminationStatus))completionBlock
{
    return [[self alloc] initWithLaunchPath:launchPath arguments:arguments outputBlock:outputBlock completionBlock:completionBlock];
}

- (void)start
{
    if ([self isCancelled]) {
        [self changeFinishedState:YES];
        return;
    }
    
    [self changeExecutingState:YES];
    
    // configure and launch task instance
    [_task setStandardOutput:[NSPipe pipe]];
    
    // register for task termination notification
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(taskExited:) name:NSTaskDidTerminateNotification object:_task];
    
    // read handler for asynchronous output
    [[[_task standardOutput] fileHandleForReading] setReadabilityHandler:^(NSFileHandle *file) {
        NSData *data = [file availableData];
        NSString *output = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        if (![output isEqualToString:@"\n"]) {
            [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                outputCallback(output);
            }];
        }
    }];
    
    [_task launch];
    
    // spin run loop periodically while operation is alive, allowing for task
    // termination notification, and test for cancellation
    while (!self.isFinished) {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:0.1]];
        
        if ([self isCancelled] && !_waitingForTaskToExit) {
            _waitingForTaskToExit = YES;
            [_task interrupt];
        }
    }
}

- (BOOL)isConcurrent
{
    return YES;
}

- (BOOL)isExecuting
{
    return _executing;
}

- (BOOL)isFinished
{
    return _finished;
}

- (void)changeFinishedState:(BOOL)finished
{
    [self willChangeValueForKey:@"isFinished"];
    _finished = finished;
    [self didChangeValueForKey:@"isFinished"];
}

- (void)changeExecutingState:(BOOL)executing
{
    [self willChangeValueForKey:@"isExecuting"];
    _executing = executing;
    [self didChangeValueForKey:@"isExecuting"];
}

- (void)taskExited:(NSNotification *)notification
{
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        completionCallback([_task terminationStatus]);
    }];
    
    // stop reading and cleanup file handle's structures
    [[[_task standardOutput] fileHandleForReading] setReadabilityHandler:nil];
    
    // update operation state
    [self changeExecutingState:NO];
    [self changeFinishedState:YES];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NSTaskDidTerminateNotification object:_task];
}

@end
