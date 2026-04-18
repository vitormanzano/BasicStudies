# Reverting changes in git

<p>Exists two main ways to undo changes in git --  one of them is using git reset and the other git revert. </p>

<p> git reset will move the branch to back like if the commit never even have existed.</p>
```
git reset HEAD~1
```

<p> Besides the reset work really well in local branches, this method not work with remote branches the other people are using. To revert changes and be able to share this changes with others we need to use the git revert</p>
```
git revert HEAD
```
<p> The revert creates other commit. The changes for the commit is the last commit. </p>
