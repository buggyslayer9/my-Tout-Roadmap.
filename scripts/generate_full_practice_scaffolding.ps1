$ErrorActionPreference = 'Stop'

function Get-TitleCase([string]$text) {
    $culture = [System.Globalization.CultureInfo]::InvariantCulture
    return $culture.TextInfo.ToTitleCase($text.ToLower())
}

Get-ChildItem -Directory | Where-Object { $_.Name -like 'chapter_*' } | Sort-Object Name | ForEach-Object {
    $parts = $_.Name -split '_', 3
    $number = [int]$parts[1]
    $slug = $parts[2]
    $title = Get-TitleCase(($slug -replace '_', ' '))
    $chapterNum = '{0:D2}' -f $number

    $reviewPath = Join-Path $_.FullName '90_review_questions.md'
    if (-not (Test-Path $reviewPath)) {
        $review = @(
            "# Chapter $chapterNum Review Questions: $title",
            '',
            'Use these questions after finishing the main lesson files.',
            '',
            '## Concept Questions',
            "- What are the three most important ideas in $title?",
            '- Which part still feels unclear or fragile?',
            '- How does this chapter connect to earlier chapters in the roadmap?',
            '',
            '## Practical Questions',
            '- What would I build with this knowledge right now?',
            '- What is one common mistake a beginner could make here?',
            '- What should I practice again before moving forward?',
            '',
            '## Reflection',
            '- What clicked for me in this chapter?',
            '- What would I explain differently to another learner?',
            '- What project idea became more realistic after this chapter?'
        ) -join "`r`n"
        Set-Content -Path $reviewPath -Value $review -Encoding utf8
    }

    $mistakesPath = Join-Path $_.FullName '91_common_mistakes.md'
    if (-not (Test-Path $mistakesPath)) {
        $mistakes = @(
            "# Chapter $chapterNum Common Mistakes: $title",
            '',
            "This file highlights frequent mistakes learners make while studying $title.",
            '',
            '## Common Mistakes',
            '- Skipping the examples and reading only theory.',
            '- Moving on before the assignment feels comfortable.',
            '- Memorizing syntax without understanding the underlying idea.',
            '- Building something too large before mastering the chapter basics.',
            '',
            '## Recovery Advice',
            '- Re-type one example by hand.',
            '- Shrink the problem to one tiny exercise.',
            '- Write down the confusing part in plain language.',
            '- Revisit the chapter learning guide and self-check questions.'
        ) -join "`r`n"
        Set-Content -Path $mistakesPath -Value $mistakes -Encoding utf8
    }

    $bonusAssignmentPath = Join-Path $_.FullName ("assignment_{0}_bonus.md" -f $chapterNum)
    if (-not (Test-Path $bonusAssignmentPath)) {
        $bonus = @(
            "# Bonus Assignment $chapterNum",
            '',
            "## Goal",
            '',
            "Deepen your understanding of **$title** with one more focused practice task.",
            '',
            '## Task',
            '',
            "- Review the main lesson files in $title.",
            '- Build or describe one additional example beyond the chapter assignment.',
            '- Write down one failure case, edge case, or design tradeoff.',
            '- Summarize what changed between your first understanding and your current understanding.',
            '',
            '## Deliverable',
            '',
            '- A short working example, note, or prototype',
            '- A short reflection on one mistake or improvement',
            '',
            '## Stretch Goals',
            '',
            '- Turn the exercise into a reusable helper or component.',
            '- Add validation, error handling, or tests where relevant.',
            '- Connect this chapter to a later project idea.'
        ) -join "`r`n"
        Set-Content -Path $bonusAssignmentPath -Value $bonus -Encoding utf8
    }

    $miniProjectPath = Join-Path $_.FullName ("mini_project_{0}.md" -f $chapterNum)
    if (-not (Test-Path $miniProjectPath)) {
        $mini = @(
            "# Mini Project $chapterNum",
            '',
            "Build a small project that proves you can apply **$title** in practice.",
            '',
            '## Goals',
            '',
            '- Keep the scope small enough to finish.',
            '- Use the key ideas from the chapter intentionally.',
            '- Produce something you can revisit later.',
            '',
            '## Suggested Scope',
            '',
            '- One main workflow or feature',
            '- One handled edge case or error state',
            '- A short note explaining your design choices',
            '',
            '## Stretch Goals',
            '',
            '- Make the structure cleaner.',
            '- Add one quality improvement such as validation, testing, or documentation.',
            '- Prepare the project to connect with a later chapter.'
        ) -join "`r`n"
        Set-Content -Path $miniProjectPath -Value $mini -Encoding utf8
    }

    $bigProjectPath = Join-Path $_.FullName ("big_project_{0}.md" -f $chapterNum)
    if (-not (Test-Path $bigProjectPath)) {
        $big = @(
            "# Big Project $chapterNum",
            '',
            "Use **$title** in a larger, more portfolio-shaped project.",
            '',
            '## Goals',
            '',
            '- Apply the chapter in a product or system context.',
            '- Combine this chapter with earlier material.',
            '- Practice planning, implementation, and reflection.',
            '',
            '## Suggested Features',
            '',
            '- A clear user or developer workflow',
            '- Meaningful structure and organization',
            '- One reliability or quality improvement',
            '- A short README or design note',
            '',
            '## Stretch Goals',
            '',
            '- Add persistence, deployment, or automation when relevant.',
            '- Connect the project to a later chapter track.',
            '- Turn the result into a portfolio artifact.'
        ) -join "`r`n"
        Set-Content -Path $bigProjectPath -Value $big -Encoding utf8
    }
}

Write-Output 'Generated review lessons, bonus assignments, mini projects, and big projects for all chapter folders.'
