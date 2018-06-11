#A Computer Vision Based Intelligent Mobile Robot

This code is for a graduation project. The repository contains all code needed to operate a wheeled robot controlled over the internet and identifies objects

## Add issues
If there is any task that needs to be handled and should not be forgotten. at an issue for that task immediately and assign it to the appropriate team member

## How to contribute
For original team members, feel free to commit to the master branch immediately if it's your own project part and no one else need to edit it or make changes to their code after your commits. Else please add a pull request in a new branch and ask other members to review it or add their edits to it directly before merging to the master branch. These are some detailed instructions:

1) Create a topic branch from master branch. If possible, each topic branch should not depend on any code from other topic branches and should always be based on the master branch.

- git checkout master
- git pull
- git checkout -b my-topic-branch

2) Make the changes, pull the latest master into your topic branch, test that everything works locally

- git checkout my-topic-branch
- git pull
- git merge master (into my-topic-branch)

3) If everything works locally, push your topic branch to Github.

- git checkout my-topic-branch
- git push origin my-topic-branch

4) Create a pull request for your topic branch to be accepted into master here on Github. Add description in your pull request `resolves #<issue_number>`. It's a [keyword](https://help.github.com/articles/closing-issues-using-keywords/) that automatically closes the issue when a pull request is merged.

## Software requirements
Add software requirements to `.txt` files on the root directory.

## Documentation
The graduation project book exists in the `docs` directory. It's preferable to add seperate documentations for what ever you work on on this directory to be added later to the graduation book.
if there is any source of information you used put it's link down  in the resources section in the `README.md` file

## Resources
- Video streaming online using flask: [video streaming with Flask](http://blog.miguelgrinberg.com/post/video-streaming-with-flask) and its follow-up [Flask Video Streaming Revisited](http://blog.miguelgrinberg.com/post/flask-video-streaming-revisited).
