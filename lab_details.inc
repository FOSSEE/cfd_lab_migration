<?php
function lab_migration_completed_labs_all()
  {
    $output = "";
    //$query = "SELECT * FROM {lab_migration_proposal} WHERE approval_status = 3";
    $query = db_select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('approval_status', 3);
    $query->orderBy('approval_date', DESC);
    $result = $query->execute();
    //$result = db_query($query);
    if ($result->rowCount() == 0)
      {
        $output .= "We will in process to update lab migration data";
      }
    else
      {
        $preference_rows = array();
        $i = $result->rowCount();
        while ($row = $result->fetchObject())
          {
            $approval_date = date("Y", $row->approval_date);
            if($row->problem_statement_file == ''){
              $problem_statement_file = "NA";
            }
            else{
              $problem_statement_file = l('View', 'lab-migration/download/problem-statement/' . $row->id);
            }
            $preference_rows[] = array(
                $i,
                $row->university,
                l($row->lab_title, "lab-migration/experiments-list/" . $row->id),
                $problem_statement_file,
                $approval_date
            );
            $i--;
          }
        $preference_header = array(
            'No',
            'Institute',
            'Lab',
            'Problem Statement',
            'Year'
        );
        $output .= theme('table', array(
            'header' => $preference_header,
            'rows' => $preference_rows
        ));
      }
    return $output;
  }
function lab_migration_labs_progress_all()
  {
    $page_content = "";
    //$query = "SELECT * FROM {lab_migration_proposal} WHERE approval_status = 1 and solution_status = 2";
    $query = db_select('lab_migration_proposal');
    $query->fields('lab_migration_proposal');
    $query->condition('approval_status', 1);
    $query->condition('solution_status', 2);
    $result = $query->execute();
    if ($result->rowCount() == 0)
      {
        $page_content .= "We will in process to update lab migration data";
      }
    else
      {
        //$result = db_query($query);
        $page_content .= "<ol reversed>";
        while ($row = $result->fetchObject())
          {
            $page_content .= "<li>";
            $page_content .= $row->university . " ({$row->lab_title})";
            $page_content .= "</li>";
          }
        $page_content .= "</ol>";
      }
    return $page_content;
  }
