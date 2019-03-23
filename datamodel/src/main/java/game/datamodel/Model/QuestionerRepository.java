package game.datamodel.Model;

import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface QuestionerRepository extends JpaRepository<Questioner, Integer> {
    List<Questioner> findAll();
}
