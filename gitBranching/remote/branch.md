# Remote branch

Remote branches reflect the state of remote repositories (since the last time you talked to them). They help you understand the differences between local work and currently public work -- a critical step to take before sharing your work with others.

Remote branches have the special property of, when they suffer a checkout, they put the repository in "Detached HEAD" mode. Git does this on purpose, because you cannot work on these branches directly; you are required to work elsewhere and only then share your work with the remote (after that, the remote branches will be updated).
\o means origin. It's the name to the remote repository, is the standard name.

## Fetch
download data from a remote repository -- the command for this is conveniently called git fetch.

Download the commits that the remote repository has but that are missing in the local repository, and...
Updates the reference to which remote braches (for example, o/main) are pointing
Fetch just download, doesn't change your local.

## Pull
There are actually many ways to do it -- once you have the new commits available locally, you can embed them as if they were normal commits in other branches. This means that you can execute commands like these below:

git cherry-pick o/main
git rebase o/main
git merge o/main
Etc., etc.
The workflow of running fetch to download the remote changes and then ummerge them is so common that Git actually provides a command that does both things at once! This command is git pull.

## Push
Share my work. Send my work to the origin.

## Merging work with origin and local 
Imagine that you cloned a repository on Monday and started working on a new feature. On Friday you are ready to publish the functionality -- but, oh no! His colleagues wrote a lot of code during the week, making their functionality obsolete. They also published these commits in the remote repository that you share, so now your work is based on an old version of the project, which is no longer relevant.
The git doesn't allow you to push your changes, because he didn't know what he do with the new code.

Now if we do a rebase before the push.

Boom! We updated the local representation of the remote repository with git fetch, rebased our work to reflect the new changes in the remote repository, and then sent our changes with git push.

## Remote rejected
If you work in a large collaborative team it is likely that the main will be blocked and need some Pull Request processes to join changes. If you commit directly to the main locally and try to push you will see a message similar to this:

! [remote rejected] main -> main (TF402455: Pushes to this branch are not permitted; you must use a pull request to update this branch.)
The remote repository rejected the push of commits directly to the main because of the main policy requiring the use of pull requests.

## Branch
git branch -u o/main

configure the branch to track o/main. This command will get the branch that our HEAD is.

or we specify: git branch o/main foo

## Push parameters
git push <remote repo> <place>

git push origin main

Go to the branch called "main" in my local repository, take all the commits, then go to the "main" branch in the remote repository called "origin". Put any commits that are missing in this branch, and then tell me when it's ready.

To specify both the origin and destination of the <lugar>, we simply join the two using a colon:

git push origin <origin>:<destiny>

## Strange things
git push origin :side
git fetch origin :bugFix
This means you are passing nothing.

This push will remove the branch side from the origin. Because you are passing nothing to him.










