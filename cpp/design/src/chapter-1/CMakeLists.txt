cmake_minimum_required(VERSION 3.1)

testable(creator)

testable(chapter.1.5)
testable(chapter.1.7)
expect_segfault(chapter.1.7 PUBLIC_DTOR)
expect_compilation_failure(chapter.1.7 PROTECTED_DTOR)
testable(chapter.1.8)
expect_compilation_failure(chapter.1.8 UNSUPPORTED_CREATION_POLICY_API)
testable(chapter.1.9)
expect_segfault(chapter.1.9 NO_CHECKING_NULLPTR)
testable(chapter.1.10)
