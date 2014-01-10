## MRWorker

`MRWorker` is a tiny Objective-C library intended to make interaction with command-line programs effortless.

A simple example:

```objc
MRWorkerOperation *operation = [MRWorkerOperation workerOperationWithLaunchPath:@"/bin/ls" arguments:@[@"-al", @"/"] outputBlock:^(NSString *output) {
    // respond to program output
    ...
} completionBlock:^(int terminationStatus) {
    // respond to program termination
    ...
}

[[MRWorkerOperationQueue sharedQueue] addOperation:operation];
```

See [CocoaDocs](http://cocoadocs.org/docsets/MRWorker/) for additional documentation.

## Contributions
If you would like to contribute to the project, [fork the repository](https://help.github.com/articles/fork-a-repo), make your code changes, then submit a [pull request](https://help.github.com/articles/using-pull-requests) with a brief description of your feature or bug fix.

## License
`MRWorker` is provided under the terms of the [MIT License](http://opensource.org/licenses/mit-license.php).

## Contact
Email me at [marc.ransome@fidgetbox.co.uk](mailto:marc.ransome@fidgetbox.co.uk) or tweet [@marcransome](http://www.twitter.com/marcransome).
