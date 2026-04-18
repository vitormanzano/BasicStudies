# Git Rebase

The second form to combine different works between branchs is using rebase. Him gets a group of commits, "copy" them, and put them in other place.

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
    git checkout bugFix
</li
<li>
    git rebase main
</li>
</ul>



