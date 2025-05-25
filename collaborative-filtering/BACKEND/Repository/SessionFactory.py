from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, Session
from contextlib import contextmanager
from BACKEND.config import DATABASE_PATH

# Engine and Session Factory
engine = create_engine(f'sqlite:///{DATABASE_PATH}', echo=True)
SessionFactory = sessionmaker(bind=engine)

@contextmanager
def get_session() -> Session :
    session = SessionFactory()
    try:
        yield session  # Provides the session to the block under `with`
        session.commit()  # Commits the transaction if no exceptions occur
    except Exception as e:
        session.rollback()  # Rollback any changes made during the transaction
        raise e  # Re-raise the exception to be handled outside
    finally:
        session.close()  # Ensures the session is closed in all cases
