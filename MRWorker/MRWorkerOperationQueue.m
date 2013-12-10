//
//  MRWorker.m
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

#import "MRWorkerOperationQueue.h"
#import "MRWorkerOperation.h"

#ifndef __has_feature
#define __has_feature(x) 0 // for compatibility with non-clang compilers
#endif

#if !__has_feature(objc_arc)
#error MRWorkerOperationQueue must be built with ARC.
#endif

@interface MRWorkerOperationQueue ()
{
    NSOperationQueue *_backgroundQueue;
}

@end

@implementation MRWorkerOperationQueue

+ (MRWorkerOperationQueue *)sharedQueue
{
    static dispatch_once_t onceToken;
    static MRWorkerOperationQueue *workerOperationQueue = nil;
    
    if (!workerOperationQueue) {
        dispatch_once(&onceToken, ^{
            workerOperationQueue = [[self alloc] init];
        });
    }
    
    return workerOperationQueue;
}

- (instancetype)init
{
    if (self = [super init]) {
        _backgroundQueue = [[NSOperationQueue alloc] init];
    }
    
    return self;
}

- (void)addOperation:(MRWorkerOperation *)operation
{
    [_backgroundQueue addOperation:operation];
}

@end
