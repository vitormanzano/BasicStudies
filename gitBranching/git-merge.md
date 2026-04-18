# Git Merge

Git merge creates a special commit that has two unique parents. This means "I wanna include all the work of this parent with the work from that parent, with them incestors"

<ul>
<li>
    git checkout -b bugFix -> Creates the branch bugFix
</li>
<li>
    git commit
</li>
<li>
    git checkout main
</li>
<li>
    git commit
</li>

<li>
   git merge bugFix -> Now the current commit have two parents. Commit from bugfix and the previous commit before main commit 
</li>
</ul>

