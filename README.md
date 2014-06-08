# MRWorker

[![Build Status](http://img.shields.io/travis/marcransome/MRWorker.svg?style=flat)](https://travis-ci.org/marcransome/MRWorker) [![Version](https://img.shields.io/cocoapods/v/MRWorker.svg?style=flat)](http://cocoadocs.org/docsets/MRWorker) [![Platform](https://img.shields.io/cocoapods/p/MRWorker.svg?style=flat)](http://cocoadocs.org/docsets/MRWorker)

`MRWorker` is a tiny Objective-C library for running command-line programs asynchronously and observing their output.

A simple example:

```objc
MRWorkerOperation *operation = [MRWorkerOperation workerOperationWithLaunchPath:@"/bin/ls" arguments:@[@"-al", @"/"] outputBlock:^(NSString *output) {
    // buffer/process program output
    ...
} completionBlock:^(int terminationStatus) {
    // respond to program termination
    ...
}

[[MRWorker sharedWorker] addOperation:operation];
```

## Contributions
If you would like to contribute to the project, [fork the repository](https://help.github.com/articles/fork-a-repo), make your code changes, then submit a [pull request](https://help.github.com/articles/using-pull-requests) with a brief description of your feature or bug fix.

## License
`MRWorker` is provided under the terms of the [MIT License](http://opensource.org/licenses/mit-license.php).

## Contact
Email me at [marc.ransome@fidgetbox.co.uk](mailto:marc.ransome@fidgetbox.co.uk) or tweet [@marcransome](http://www.twitter.com/marcransome).
