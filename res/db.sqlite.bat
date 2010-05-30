#
# Example based on test.sqlite db. Try to detect the point with ID=60 as the closest point.
#
# Runtime arguments:
#  [1] database name
#  [2] reference latitude
#  [3] reference longitude
#  [4] reference timestamp
#  [5] ..[N] names to change

@echo off

DateManipulatorD.exe db.sqlite 52.5018387 13.4338551 1989-11-20T17:15:25Z Dan
pause

@echo on