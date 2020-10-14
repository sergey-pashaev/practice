cmake_minimum_required(VERSION 3.1)

unit_test(creator)

unit_test(chapter.1.5)
unit_test(chapter.1.7)
expect_segfault(chapter.1.7 PUBLIC_DTOR)
expect_compilation_failure(chapter.1.7 PROTECTED_DTOR)
unit_test(chapter.1.8)
expect_compilation_failure(chapter.1.8 UNSUPPORTED_CREATION_POLICY_API)
unit_test(chapter.1.9)
expect_segfault(chapter.1.9 NO_CHECKING_NULLPTR)
unit_test(chapter.1.10)
