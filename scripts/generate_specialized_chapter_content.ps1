$ErrorActionPreference = 'Stop'

function Get-TitleCase([string]$text) {
    $culture = [System.Globalization.CultureInfo]::InvariantCulture
    return $culture.TextInfo.ToTitleCase($text.ToLower())
}

function Get-Phase([int]$number) {
    if ($number -le 10) { return 'c' }
    if ($number -le 20) { return 'gtk' }
    if ($number -le 26) { return 'rust' }
    if ($number -le 43) { return 'systems' }
    if ($number -le 58) { return 'web' }
    if ($number -le 62) { return 'mobile' }
    return 'devops'
}

function Get-AssignmentIdeas([string]$phase, [string]$title) {
    switch ($phase) {
        'c' { return @(
            @{ Level='Easy'; Name='Trace The Program'; Hint='Write the output on paper before you run the code.' },
            @{ Level='Easy'; Name='Repair A Small Bug'; Hint='Look for off-by-one mistakes, bad input assumptions, or missing initialization.' },
            @{ Level='Medium'; Name='Refactor Into Functions'; Hint='Split repeated logic into small named helpers.' },
            @{ Level='Hard'; Name='Handle Bad Input'; Hint='Add validation and retry loops instead of assuming perfect input.' },
            @{ Level='Expert'; Name='Turn It Into A Small Tool'; Hint='Add file input, better output formatting, or reusable helpers.' }
        ) }
        'gtk' { return @(
            @{ Level='Easy'; Name='Rebuild The Example UI'; Hint='Keep the first version small and focus on layout correctness.' },
            @{ Level='Easy'; Name='Add One More Widget'; Hint='Choose a widget that matches the user action clearly.' },
            @{ Level='Medium'; Name='Connect State To UI'; Hint='Make the UI reflect a real change instead of only printing to the terminal.' },
            @{ Level='Hard'; Name='Improve UX Flow'; Hint='Reduce unnecessary dialogs and make feedback clearer.' },
            @{ Level='Expert'; Name='Organize Into Multiple Files'; Hint='Separate UI creation, state, and handlers.' }
        ) }
        'rust' { return @(
            @{ Level='Easy'; Name='Explain The Type Flow'; Hint='Write what each value owns, borrows, or returns.' },
            @{ Level='Easy'; Name='Rewrite Without Copying'; Hint='Type the program from memory and then compare.' },
            @{ Level='Medium'; Name='Model It With Enums Or Structs'; Hint='Use the type system to make invalid states harder.' },
            @{ Level='Hard'; Name='Add Error Handling'; Hint='Replace panic-style thinking with Result-based flow.' },
            @{ Level='Expert'; Name='Package It As A Small Crate'; Hint='Extract one reusable concept into a library-style API.' }
        ) }
        'systems' { return @(
            @{ Level='Easy'; Name='Describe The OS Boundary'; Hint='Write which parts belong to the program and which belong to the OS.' },
            @{ Level='Easy'; Name='Inspect One Failure Case'; Hint='Choose one real resource failure such as missing file or denied permission.' },
            @{ Level='Medium'; Name='Add Safer Error Reporting'; Hint='Return useful exit codes and clearer diagnostics.' },
            @{ Level='Hard'; Name='Design A Small Protocol Or Service'; Hint='Write the rules before writing the code.' },
            @{ Level='Expert'; Name='Turn The Chapter Into A Real Tool'; Hint='Think like a systems builder: clear inputs, clear outputs, clear failure behavior.' }
        ) }
        'web' { return @(
            @{ Level='Easy'; Name='Rebuild A Small Flow'; Hint='Choose one page, route, or API call and keep the scope tiny.' },
            @{ Level='Easy'; Name='Inspect The Data Shape'; Hint='Write the request, response, or model shape before coding.' },
            @{ Level='Medium'; Name='Add Validation And Error States'; Hint='Handle bad input and empty results intentionally.' },
            @{ Level='Hard'; Name='Connect Frontend To Backend'; Hint='Trace the full request cycle from user action to stored data.' },
            @{ Level='Expert'; Name='Ship A Product Slice'; Hint='Build one feature as if it belonged in a real app, including auth, data, or deployment thinking when relevant.' }
        ) }
        'mobile' { return @(
            @{ Level='Easy'; Name='Compose One Screen Well'; Hint='Break the UI into small widgets with clear roles.' },
            @{ Level='Easy'; Name='Handle Empty And Loading States'; Hint='Do not design only the success path.' },
            @{ Level='Medium'; Name='Add Local State Cleanly'; Hint='Keep state close to the widget that owns it.' },
            @{ Level='Hard'; Name='Connect To A Simple API'; Hint='Plan loading, error, success, and empty states.' },
            @{ Level='Expert'; Name='Turn It Into A Small App Flow'; Hint='Use navigation, reusable widgets, and one meaningful user task.' }
        ) }
        default { return @(
            @{ Level='Easy'; Name='Summarize The Workflow'; Hint='Write the chapter flow in your own words.' },
            @{ Level='Easy'; Name='Find One Failure Mode'; Hint='Think about what breaks first in real use.' },
            @{ Level='Medium'; Name='Improve The Structure'; Hint='Separate concerns and make the workflow clearer.' },
            @{ Level='Hard'; Name='Automate One Step'; Hint='Reduce repeated manual work.' },
            @{ Level='Expert'; Name='Make It Production-Shaped'; Hint='Add verification, rollback, or documentation thinking.' }
        ) }
    }
}

function Get-MiniIdeas([string]$phase, [string]$title) {
    switch ($phase) {
        'c' { return @('A tiny terminal utility', 'A parsing or formatting helper', 'A small file-based tracker', 'A calculator or converter', 'A defensive input-handling exercise') }
        'gtk' { return @('A small desktop utility window', 'A form-based app', 'A note or task widget', 'A styled GTK tool', 'A multi-widget productivity toy') }
        'rust' { return @('A CLI utility', 'A typed data model explorer', 'A small parser', 'A reusable crate', 'A concurrent or async experiment') }
        'systems' { return @('A file or process tool', 'A socket-based service', 'A shell-like helper', 'A system inspection utility', 'A service or protocol prototype') }
        'web' { return @('A single-page product slice', 'A typed API-backed page', 'A form workflow', 'A dashboard view', 'A solo-builder SaaS starter feature') }
        'mobile' { return @('A one-screen Flutter app', 'A tracker UI', 'A list-detail app', 'A stateful dashboard', 'An API-backed mobile prototype') }
        default { return @('A release checklist tool', 'A CI or workflow improvement', 'A deployment helper', 'A monitoring note or dashboard idea', 'An operations support utility') }
    }
}

function Get-BigIdeas([string]$phase, [string]$title) {
    switch ($phase) {
        'c' { return @('A reusable C toolkit', 'A small command-line application suite', 'A file-processing utility with tests') }
        'gtk' { return @('A polished desktop productivity app', 'A multi-window or multi-view GTK project', 'A themed Linux desktop utility') }
        'rust' { return @('A reusable Rust crate with docs and tests', 'A robust CLI application', 'A small service or typed workflow tool') }
        'systems' { return @('A systems utility with clear failure handling', 'A service-oriented tool with logging and cleanup', 'A protocol-driven or OS-facing project') }
        'web' { return @('A solo-builder SaaS starter', 'A full-stack app with auth and persistence', 'A feature-complete product slice with billing or admin flow') }
        'mobile' { return @('A mobile productivity app', 'An offline-friendly Flutter app', 'A cross-screen app with API integration and local state') }
        default { return @('A CI/CD pipeline project', 'A deployment-ready service pack', 'An operationally documented production-style demo') }
    }
}

Get-ChildItem -Directory | Where-Object { $_.Name -like 'chapter_*' } | Sort-Object Name | ForEach-Object {
    $parts = $_.Name -split '_', 3
    $number = [int]$parts[1]
    $slug = $parts[2]
    $title = Get-TitleCase(($slug -replace '_', ' '))
    $phase = Get-Phase $number
    $chapterNum = '{0:D2}' -f $number

    $lessonAPath = Join-Path $_.FullName '92_patterns_and_build_strategies.md'
    if (-not (Test-Path $lessonAPath)) {
        $lessonA = @(
            "# Chapter $chapterNum Patterns And Build Strategies: $title",
            '',
            "This lesson adds one more layer of practical thinking to **$title**.",
            '',
            '## What To Look For',
            '- repeated patterns you can name clearly',
            '- common structures that make the chapter easier to apply',
            '- small strategies that help you build with less confusion',
            '',
            '## Builder Mindset',
            '- start with one thin working slice',
            '- keep the first version smaller than you want',
            '- add one quality improvement after the core works',
            '',
            '## Learning Check',
            '- Can I name one useful pattern from this chapter?',
            '- Can I explain how I would build a tiny version first?'
        ) -join "`r`n"
        Set-Content -Path $lessonAPath -Value $lessonA -Encoding utf8
    }

    $lessonBPath = Join-Path $_.FullName '93_debugging_review_and_extension.md'
    if (-not (Test-Path $lessonBPath)) {
        $lessonB = @(
            "# Chapter $chapterNum Debugging, Review, And Extension: $title",
            '',
            "This lesson helps you review and extend **$title** instead of stopping at the first working example.",
            '',
            '## Review Questions',
            '- Where does this chapter usually fail in real code?',
            '- What should be tested, validated, or reviewed more carefully?',
            '- What would I extend if this became part of a larger project?',
            '',
            '## Extension Ideas',
            '- add one edge case',
            '- add one readability improvement',
            '- add one stronger design decision',
            '',
            '## Learning Check',
            '- Can I debug a small failure in this topic?',
            '- Can I extend the example without rewriting everything?'
        ) -join "`r`n"
        Set-Content -Path $lessonBPath -Value $lessonB -Encoding utf8
    }

    $assignmentPath = Join-Path $_.FullName ("assignment_{0}_levels.md" -f $chapterNum)
    if (-not (Test-Path $assignmentPath)) {
        $ideas = Get-AssignmentIdeas -phase $phase -title $title
        $lines = @(
            "# Chapter $chapterNum Levels Assignment Pack: $title",
            '',
            "This chapter now includes a multi-level assignment pack inspired by practice platforms such as LeetCode and Codewars.",
            '',
            'Work through the levels in order. Stop when the chapter starts feeling shaky, then review and come back later.',
            ''
        )

        foreach ($idea in $ideas) {
            $lines += @(
                "## $($idea.Level): $($idea.Name)",
                "- Goal: apply $title in a focused task.",
                "- Hint: $($idea.Hint)",
                "- Output: a working example, note, or small program that proves the idea.",
                ''
            )
        }

        $lines += @(
            '## Scoring Idea',
            '- 1 point for Easy',
            '- 2 points for Medium',
            '- 3 points for Hard',
            '- 5 points for Expert',
            '',
            'Try to build a steady practice streak instead of chasing perfect solutions on the first attempt.'
        )

        Set-Content -Path $assignmentPath -Value ($lines -join "`r`n") -Encoding utf8
    }

    $miniIdeasPath = Join-Path $_.FullName ("mini_project_{0}_ideas.md" -f $chapterNum)
    if (-not (Test-Path $miniIdeasPath)) {
        $ideas = Get-MiniIdeas -phase $phase -title $title
        $lines = @(
            "# Chapter $chapterNum Mini Project Ideas: $title",
            '',
            "Use these ideas to build short projects after studying **$title**.",
            ''
        )
        $index = 1
        foreach ($idea in $ideas) {
            $lines += @(
                "## Idea $index",
                "- $idea",
                "- Goal: keep it small enough to finish and review.",
                "- Hint: connect it directly to the strongest concept in $title.",
                ''
            )
            $index++
        }
        Set-Content -Path $miniIdeasPath -Value ($lines -join "`r`n") -Encoding utf8
    }

    $bigIdeasPath = Join-Path $_.FullName ("big_project_{0}_ideas.md" -f $chapterNum)
    if (-not (Test-Path $bigIdeasPath)) {
        $ideas = Get-BigIdeas -phase $phase -title $title
        $lines = @(
            "# Chapter $chapterNum Big Project Ideas: $title",
            '',
            "These larger ideas help turn **$title** into a portfolio or milestone project.",
            ''
        )
        $index = 1
        foreach ($idea in $ideas) {
            $lines += @(
                "## Big Idea $index",
                "- $idea",
                "- Goal: combine this chapter with earlier roadmap material.",
                "- Hint: document scope, architecture, and one realistic failure case before you build.",
                ''
            )
            $index++
        }
        Set-Content -Path $bigIdeasPath -Value ($lines -join "`r`n") -Encoding utf8
    }
}

Write-Output 'Generated specialized lessons, level-based assignments, and fresh mini/big project idea packs for all chapter folders.'
