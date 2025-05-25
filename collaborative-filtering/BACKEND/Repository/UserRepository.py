from typing import Optional
from sqlalchemy.orm import Session
from BACKEND.Models.models import User  # Assuming the User class is in the models module

class UserRepository:
    def __init__(self, session: Session):
        self.session = session

    def create(self, in_user: User) -> User:
        """
        Create a new user.
        """
        user = User(
            id=in_user.id,
            age=in_user.age,
            gender=in_user.gender,
            occupation=in_user.occupation,
            zip_code=in_user.zip_code
        )
        self.session.add(user)
        self.session.commit()
        return user

    def get_by_id(self, user_id: int) -> Optional[User]:
        """
        Get a user by its ID.
        """
        return self.session.query(User).filter(User.id == user_id).first()

    def get_all(self) -> list:
        """
        Get all users.
        """
        return self.session.query(User).all()

    def update(self, user_id: int, in_user: User) -> Optional[User]:
        """
        Update a user by its ID.
        """
        user = self.get_by_id(user_id)
        if user:
            if in_user.age is not None:
                user.age = in_user.age
            if in_user.gender:
                user.gender = in_user.gender
            if in_user.occupation:
                user.occupation = in_user.occupation
            if in_user.zip_code:
                user.zip_code = in_user.zip_code

            self.session.commit()
            return user
        return None

    def delete(self, user_id: int) -> bool:
        """
        Delete a user by its ID.
        """
        user = self.get_by_id(user_id)
        if user:
            self.session.delete(user)
            self.session.commit()
            return True
        return False
