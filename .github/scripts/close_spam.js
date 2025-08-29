module.exports = async ({ github, context }) => {
  const { data } = await github.rest.repos.getCollaboratorPermissionLevel({
    ...context.repo,
    username: context.actor
  });
  if (!data.user.permissions.triage) {
    await github.log.error("Workflow called with insufficient permissions!");
    return;
  }

  let target = context.payload.issue;
  if (target) {
    await github.rest.issues.update({
      ...context.repo,
      issue_number: target.number,
      state: "closed",
      state_reason: "not_planned",
      title: "[spam]",
      body: "",
      type: null,
    });
  } else {
    target = context.payload.pull_request;
    await github.rest.pulls.update({
      ...context.repo,
      pull_number: target.number,
      state: "closed",
      title: "[spam]",
      body: "",
    });
  }

  await github.rest.issues.lock({
    ...context.repo,
    issue_number: target.number,
    lock_reason: "spam",
  });
};
