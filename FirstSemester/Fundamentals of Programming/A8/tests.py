import unittest
from datetime import date

from src.domain import Student, Assignment, Grade
from src.repository import RepositoryStudents, RepositoryAssignments, RepositoryGrade


class TestStudentAssignment(unittest.TestCase):
    def __init__(self):
        self.stud_repository = RepositoryStudents
        self.assign_repository = RepositoryAssignments
        self.grade_repository = RepositoryGrade

    def test_add_student(self):
        # Create a new student
        student = Student("erw475", "John Smith", 914)
        self.stud_repository.add(student)
        students = self.stud_repository.get_all_students()
        # Check that the student's attributes are correct
        self.assertEqual(students[0], 1)
        self.assertEqual(students[1], "John Smith")
        self.assertEqual(students[2], 914)

    def test_add_assignment(self):
        # Create a new assignment
        assignment = Assignment("RBq0656", "History hw", date(1, 1, 2020))
        # Check that the assignment's attributes are correct
        self.assign_repository.add(assignment)
        assignments = self.assign_repository.get_all_assignments()
        self.assertEqual(assignments[0], "RBq0656")
        self.assertEqual(assignments[1], "History hw")
        self.assertEqual(assignments[2],date(1, 1, 2020) )

    def test_add_grade(self):
        # Create a new grade
        grade = Grade(1, 1, 85)
        # Check that the grade's attributes are correct
        self.assertEqual(grade.assignment_id, 1)
        self.assertEqual(grade.student_id, 1)
        self.assertEqual(grade.grade_value, 85)

